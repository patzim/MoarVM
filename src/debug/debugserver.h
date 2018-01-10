struct MVMDebugServerHandleTableEntry {
    MVMuint64 id;
    MVMObject *target;
};

struct MVMDebugServerHandleTable {
    MVMuint32 allocated;
    MVMuint32 used;

    MVMuint64 next_id;

    MVMDebugServerHandleTableEntry *entries;
};

struct MVMDebugServerRequestEntry {
    MVMuint16 message_type;
    MVMuint32 thread_id;
    MVMuint32 counter;
    MVMuint64 request_id;
};

struct MVMDebugServerData {
    /* Debug Server thread */
    uv_thread_t thread;

    /* Protect the debugserver-related condvars */
    uv_mutex_t mutex_cond;

    /* Protect sending data on the network */
    uv_mutex_t mutex_network_send;

    /* Protect the open requests list */
    uv_mutex_t mutex_request_list;

    /* Condition variable to tell threads to check their state for changes
     * like "i should suspend" */
    uv_cond_t tell_threads;

    /* Condition variable to tell the worker to check thread states
     * for changes like "i just suspended" */
    uv_cond_t tell_worker;

    MVMuint32 port;
    MVMuint32 thread_id;

    MVMuint64 event_id;

    MVMDebugServerHandleTable *handle_table;

    MVM_VECTOR_DECL(MVMDebugServerRequestEntry, open_requests);

    void *messagepack_data;

    MVMuint8 debugspam_network;
    MVMuint8 debugspam_protocol;
};

void MVM_debugserver_init(MVMThreadContext *tc, MVMuint32 port);
void MVM_debugserver_mark_handles(MVMThreadContext *tc, MVMGCWorklist *worklist, MVMHeapSnapshotState *snapshot);

void MVM_debugserver_notify_thread_creation(MVMThreadContext *tc);
void MVM_debugserver_notify_thread_destruction(MVMThreadContext *tc);

void MVM_debugserver_notify_thread_suspends(MVMThreadContext *tc);
void MVM_debugserver_notify_thread_resumes(MVMThreadContext *tc);
