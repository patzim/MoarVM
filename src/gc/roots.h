void MVM_gc_root_add_permanent(MVMThreadContext *tc, MVMCollectable **obj_ref);
void MVM_gc_root_add_parmanents_to_worklist(MVMThreadContext *tc, MVMGCWorklist *worklist);
void MVM_gc_root_add_frame_roots_to_worklist(MVMThreadContext *tc, MVMGCWorklist *worklist, MVMFrame *start_frame);
