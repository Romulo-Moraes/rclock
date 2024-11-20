#include <dbus/dbus.h>
#include <unistd.h>

static void configureNotification(DBusMessageIter *args, const char *summary, const char *body, const char *icon) {
    const char *app_name = "Rclock";
    dbus_uint32_t replaces_id = 0;
    int timeout = 19500;

    dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &app_name);
    dbus_message_iter_append_basic(args, DBUS_TYPE_UINT32, &replaces_id);
    dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &icon);
    dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &summary);
    dbus_message_iter_append_basic(args, DBUS_TYPE_STRING, &body);

    // Actions
    DBusMessageIter array_iter;
    dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY, "s", &array_iter);
    dbus_message_iter_close_container(args, &array_iter);

    // Hints
    DBusMessageIter dict_iter;
    dbus_message_iter_open_container(args, DBUS_TYPE_ARRAY, "{sv}", &dict_iter);
    dbus_message_iter_close_container(args, &dict_iter);

    // Timeout    
    dbus_message_iter_append_basic(args, DBUS_TYPE_INT32, &timeout);
}

static DBusMessage* createMethodCallMessage() {
    DBusMessage *msg = dbus_message_new_method_call(
        "org.freedesktop.Notifications",
        "/org/freedesktop/Notifications",
        "org.freedesktop.Notifications",
        "Notify"
    );

    return msg;
}

void sendNotification(const char *summary, const char *body) {
    DBusError err;
    DBusConnection *conn;
    DBusMessage *msg;
    DBusMessageIter args;
    const char *icon = "dialog-information";
    dbus_uint32_t serial = 0;
    
    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

    if (!conn) {
        return;
    }

    msg = createMethodCallMessage();

    if (!msg) {
        return;
    }

    dbus_message_iter_init_append(msg, &args);

    configureNotification(&args, summary, body, icon);

    dbus_connection_send(conn, msg, &serial);
    dbus_connection_flush(conn);


    dbus_message_unref(msg);
    dbus_connection_unref(conn);
}