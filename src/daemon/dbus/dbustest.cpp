#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>

bool keeprunning;
pthread_t thread;
pthread_mutex_t lock;
DBusConnection* conn;
int quitpipe[2];

void*
serverthread(void*) {
    DBusMessage* msg;
    DBusError err;
    int ret;

    printf("Listening for method calls\n");
    pipe(quitpipe);

    // initialise the error
    dbus_error_init(&err);

    // connect to the bus and check for errors
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
        return 0;
    }
    if (NULL == conn) {
        fprintf(stderr, "Connection Null\n");
        return 0;
    }

    // request our name on the bus and check for errors
    ret = dbus_bus_request_name(conn, "vandenoever.strigi",
        DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Name Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
        fprintf(stderr, "Not Primary Owner (%d)\n", ret);
        return false;
    }

    for (int i=0; i<10; ++i) {
        printf("server\n");
    }
    int fd;
    dbus_connection_get_unix_fd(conn, &fd);

    bool run;
    do {
        // block until there's activit on the port
        fd_set rfds;
        struct timeval tv;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        FD_SET(quitpipe[0], &rfds);
        printf("server\n");
        tv.tv_sec = 50000;
        tv.tv_usec = 0;
        int retval = select(fd+1, &rfds, 0, 0, &tv);
        if (retval == -1 || FD_ISSET(quitpipe[0], &rfds)) break;

        // non blocking read of the next available message
//        dbus_connection_read_write_dispatch(conn, 0);
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);
        dbus_connection_flush(conn);
        dbus_message_unref(msg);

        pthread_mutex_lock(&lock);
        run = keeprunning;
        pthread_mutex_unlock(&lock);
    } while (run);

    dbus_connection_unref(conn);
    dbus_connection_unref(conn);
    dbus_shutdown();
    printf("after dbus_shutdown\n");
    return 0;
}
void
startserver() {
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread, 0, serverthread, 0);
    keeprunning = true;
}
void
stopserver() {
    pthread_mutex_lock(&lock);
    keeprunning = false;
    pthread_mutex_unlock(&lock);
    close(quitpipe[1]);

    printf("before join\n");
    pthread_join(thread, 0);
    printf("after join\n");
    pthread_mutex_destroy(&lock);
    printf("end of stopserver\n");
}

void
clientthread() {
    printf("before sleep\n");
    sleep(1);
    printf("after sleep\n");
}

int
main() {
    startserver();

    // run client code
    clientthread();

    // stop server
    stopserver();

    return 0;
}