// generated by makecode.pl
#include "dbusxesamlivesearchinterface.h"
#include "dbusserialization.h"
#include <dbusobjectinterface.h>
#include <dbusmessagereader.h>
#include <dbusmessagewriter.h>
#include <sstream>
class PrivateDBusXesamLiveSearchInterface : public DBusObjectInterface {
private:
    DBusXesamLiveSearchInterface& impl;
    typedef void (PrivateDBusXesamLiveSearchInterface::*handlerFunction)
        (DBusMessage* msg, DBusConnection* conn);
    std::map<std::string, handlerFunction> handlers;
    DBusHandlerResult handleCall(DBusConnection*c,DBusMessage* m);
    std::string getIntrospectionXML();
    void GetState(DBusMessage* msg, DBusConnection* conn);
    void StartSearch(DBusMessage* msg, DBusConnection* conn);
    void GetHitCount(DBusMessage* msg, DBusConnection* conn);
    void GetHits(DBusMessage* msg, DBusConnection* conn);
    void NewSession(DBusMessage* msg, DBusConnection* conn);
    void CloseSession(DBusMessage* msg, DBusConnection* conn);
    void GetHitData(DBusMessage* msg, DBusConnection* conn);
    void SetProperty(DBusMessage* msg, DBusConnection* conn);
    void NewSearch(DBusMessage* msg, DBusConnection* conn);
    void GetProperty(DBusMessage* msg, DBusConnection* conn);
    void CloseSearch(DBusMessage* msg, DBusConnection* conn);
public:
    PrivateDBusXesamLiveSearchInterface(DBusXesamLiveSearchInterface& i);
};
PrivateDBusXesamLiveSearchInterface::PrivateDBusXesamLiveSearchInterface(DBusXesamLiveSearchInterface& i)
        :DBusObjectInterface("org.freedesktop.xesam.Search"), impl(i) {
    handlers["GetState"] = &PrivateDBusXesamLiveSearchInterface::GetState;
    handlers["StartSearch"] = &PrivateDBusXesamLiveSearchInterface::StartSearch;
    handlers["GetHitCount"] = &PrivateDBusXesamLiveSearchInterface::GetHitCount;
    handlers["GetHits"] = &PrivateDBusXesamLiveSearchInterface::GetHits;
    handlers["NewSession"] = &PrivateDBusXesamLiveSearchInterface::NewSession;
    handlers["CloseSession"] = &PrivateDBusXesamLiveSearchInterface::CloseSession;
    handlers["GetHitData"] = &PrivateDBusXesamLiveSearchInterface::GetHitData;
    handlers["SetProperty"] = &PrivateDBusXesamLiveSearchInterface::SetProperty;
    handlers["NewSearch"] = &PrivateDBusXesamLiveSearchInterface::NewSearch;
    handlers["GetProperty"] = &PrivateDBusXesamLiveSearchInterface::GetProperty;
    handlers["CloseSearch"] = &PrivateDBusXesamLiveSearchInterface::CloseSearch;
}
DBusHandlerResult
PrivateDBusXesamLiveSearchInterface::handleCall(DBusConnection*connection, DBusMessage* msg) {
    std::map<std::string, handlerFunction>::const_iterator h;
    const char* i = getInterfaceName().c_str();
    for (h = handlers.begin(); h != handlers.end(); ++h) {
        if (dbus_message_is_method_call(msg, i, h->first.c_str())) {
            (this->*h->second)(msg, connection);
            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}
std::string
PrivateDBusXesamLiveSearchInterface::getIntrospectionXML() {
    std::ostringstream xml;
    xml << "  <interface name='"+getInterfaceName()+"'>\n"
    << "    <method name='GetState'>\n"
    << "      <arg name='state_info' type='as' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='StartSearch'>\n"
    << "      <arg name='search' type='s' direction='in'/>\n"
    << "    </method>\n"
    << "    <method name='GetHitCount'>\n"
    << "      <arg name='search' type='s' direction='in'/>\n"
    << "      <arg name='count' type='u' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='GetHits'>\n"
    << "      <arg name='search' type='s' direction='in'/>\n"
    << "      <arg name='num' type='u' direction='in'/>\n"
    << "      <arg name='hits' type='aav' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='NewSession'>\n"
    << "      <arg name='session' type='s' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='CloseSession'>\n"
    << "      <arg name='session' type='s' direction='in'/>\n"
    << "    </method>\n"
    << "    <method name='GetHitData'>\n"
    << "      <arg name='search' type='s' direction='in'/>\n"
    << "      <arg name='hit_ids' type='au' direction='in'/>\n"
    << "      <arg name='fields' type='as' direction='in'/>\n"
    << "      <arg name='hit_data' type='aav' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='SetProperty'>\n"
    << "      <arg name='session' type='s' direction='in'/>\n"
    << "      <arg name='prop' type='s' direction='in'/>\n"
    << "      <arg name='val' type='v' direction='in'/>\n"
    << "      <arg name='new_val' type='v' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='NewSearch'>\n"
    << "      <arg name='session' type='s' direction='in'/>\n"
    << "      <arg name='query_xml' type='s' direction='in'/>\n"
    << "      <arg name='search' type='s' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='GetProperty'>\n"
    << "      <arg name='session' type='s' direction='in'/>\n"
    << "      <arg name='prop' type='s' direction='in'/>\n"
    << "      <arg name='value' type='v' direction='out'/>\n"
    << "    </method>\n"
    << "    <method name='CloseSearch'>\n"
    << "      <arg name='search' type='s' direction='in'/>\n"
    << "    </method>\n"
    << "    <signal name='StateChanged'>\n"
    << "      <arg name='state_info' type='as'/>\n"
    << "    </signal>\n"
    << "    <signal name='SearchDone'>\n"
    << "      <arg name='search' type='s'/>\n"
    << "    </signal>\n"
    << "    <signal name='HitsModified'>\n"
    << "      <arg name='search' type='s'/>\n"
    << "      <arg name='hit_ids' type='au'/>\n"
    << "    </signal>\n"
    << "    <signal name='HitsRemoved'>\n"
    << "      <arg name='search' type='s'/>\n"
    << "      <arg name='hit_ids' type='au'/>\n"
    << "    </signal>\n"
    << "    <signal name='HitsAdded'>\n"
    << "      <arg name='search' type='s'/>\n"
    << "      <arg name='count' type='u'/>\n"
    << "    </signal>\n"
    << "  </interface>\n";
    return xml.str();
}
void
PrivateDBusXesamLiveSearchInterface::GetState(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            writer << impl.GetState();
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::StartSearch(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string search;
        reader >> search;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            impl.StartSearch(search);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::GetHitCount(DBusMessage* dbm, DBusConnection* conn) {
    DBusMessageReader reader(dbm);
    std::string search;
    reader >> search;
    if (!reader.isOk()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Invalid input.");
    } else if (!reader.atEnd()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Too many arguments.");
    } else {
        dbus_message_ref(dbm);
        impl.GetHitCount(dbm, search);
    }
}
void
PrivateDBusXesamLiveSearchInterface::GetHits(DBusMessage* dbm, DBusConnection* conn) {
    DBusMessageReader reader(dbm);
    std::string search;
    uint32_t num;
    reader >> search >> num;
    if (!reader.isOk()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Invalid input.");
    } else if (!reader.atEnd()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Too many arguments.");
    } else {
        dbus_message_ref(dbm);
        impl.GetHits(dbm, search,num);
    }
}
void
PrivateDBusXesamLiveSearchInterface::NewSession(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            writer << impl.NewSession();
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::CloseSession(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string session;
        reader >> session;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            impl.CloseSession(session);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::GetHitData(DBusMessage* dbm, DBusConnection* conn) {
    DBusMessageReader reader(dbm);
    std::string search;
    std::vector<uint32_t> hit_ids;
    std::vector<std::string> fields;
    reader >> search >> hit_ids >> fields;
    if (!reader.isOk()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Invalid input.");
    } else if (!reader.atEnd()) {
        DBusMessageWriter writer(conn, dbm);
        writer.setError("Too many arguments.");
    } else {
        dbus_message_ref(dbm);
        impl.GetHitData(dbm, search,hit_ids,fields);
    }
}
void
PrivateDBusXesamLiveSearchInterface::SetProperty(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string session;
        std::string prop;
        Strigi::Variant val;
        reader >> session >> prop >> val;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            writer << impl.SetProperty(session,prop,val);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::NewSearch(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string session;
        std::string query_xml;
        reader >> session >> query_xml;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            writer << impl.NewSearch(session,query_xml);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::GetProperty(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string session;
        std::string prop;
        reader >> session >> prop;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            writer << impl.GetProperty(session,prop);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
void
PrivateDBusXesamLiveSearchInterface::CloseSearch(DBusMessage* msg, DBusConnection* conn) {
    DBusMessageWriter writer(conn, msg);
    try {
        DBusMessageReader reader(msg);
        std::string search;
        reader >> search;
        if (!reader.isOk()) {
            writer.setError("Invalid input.");
        } else if (!reader.atEnd()) {
            writer.setError("Too many arguments.");
        } else {
            impl.CloseSearch(search);
        }
    } catch (const std::exception& e) {
        writer.setError(e.what());
    } catch (...) {
        writer.setError("");
    }
}
DBusXesamLiveSearchInterface::DBusXesamLiveSearchInterface(const std::string& on, DBusConnection* c, XesamLiveSearchInterface* x) 
        :XesamLiveSearchInterface(x), object(on), conn(c), iface(new PrivateDBusXesamLiveSearchInterface(*this)) {}
DBusXesamLiveSearchInterface::~DBusXesamLiveSearchInterface() {
    delete iface;
}
void
DBusXesamLiveSearchInterface::GetHitsResponse(void* msg, const char* err,             const std::vector<std::vector<Strigi::Variant> >& hits) {
    DBusMessage* m = static_cast<DBusMessage*>(msg);
    DBusMessageWriter writer(conn, m);
    writer << hits;
    dbus_message_unref(m);
}
void
DBusXesamLiveSearchInterface::GetHitCountResponse(void* msg, const char* err, uint32_t count) {
    DBusMessage* m = static_cast<DBusMessage*>(msg);
    DBusMessageWriter writer(conn, m);
    writer << count;
    dbus_message_unref(m);
}
void
DBusXesamLiveSearchInterface::GetHitDataResponse(void* msg, const char* err,             const std::vector<std::vector<Strigi::Variant> >& hit_data) {
    DBusMessage* m = static_cast<DBusMessage*>(msg);
    DBusMessageWriter writer(conn, m);
    writer << hit_data;
    dbus_message_unref(m);
}
void
DBusXesamLiveSearchInterface::StateChanged(const std::vector<std::string>& state_info) {
    DBusMessageWriter writer(conn, object.c_str(), "org.freedesktop.xesam.Search", "StateChanged");
    writer << state_info;
}
void
DBusXesamLiveSearchInterface::SearchDone(const std::string& search) {
    DBusMessageWriter writer(conn, object.c_str(), "org.freedesktop.xesam.Search", "SearchDone");
    writer << search;
}
void
DBusXesamLiveSearchInterface::HitsModified(const std::string& search,         const std::vector<uint32_t>& hit_ids) {
    DBusMessageWriter writer(conn, object.c_str(), "org.freedesktop.xesam.Search", "HitsModified");
    writer << search << hit_ids;
}
void
DBusXesamLiveSearchInterface::HitsRemoved(const std::string& search,         const std::vector<uint32_t>& hit_ids) {
    DBusMessageWriter writer(conn, object.c_str(), "org.freedesktop.xesam.Search", "HitsRemoved");
    writer << search << hit_ids;
}
void
DBusXesamLiveSearchInterface::HitsAdded(const std::string& search, const uint32_t count) {
    DBusMessageWriter writer(conn, object.c_str(), "org.freedesktop.xesam.Search", "HitsAdded");
    writer << search << count;
}
