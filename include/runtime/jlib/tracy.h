#ifndef JX_TRACY_H
#define JX_TRACY_H

#include <stdint.h>
#ifdef TRACY_ENABLE
#include <tracy/TracyC.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct jx_tracy_api
{
#ifdef TRACY_ENABLE
	void (*set_thread_name)(const char* name);
	uint64_t (*alloc_srcloc)(uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, uint32_t color);
	uint64_t (*alloc_srcloc_name)(uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, const char* name, size_t nameSz, uint32_t color);
	TracyCZoneCtx (*emit_zone_begin)(const struct ___tracy_source_location_data* srcloc, int32_t active);
	TracyCZoneCtx (*emit_zone_begin_callstack)(const struct ___tracy_source_location_data* srcloc, int32_t depth, int32_t active);
	TracyCZoneCtx (*emit_zone_begin_alloc)(uint64_t srcloc, int32_t active);
	TracyCZoneCtx (*emit_zone_begin_alloc_callstack)(uint64_t srcloc, int32_t depth, int32_t active);
	void (*emit_zone_end)(TracyCZoneCtx ctx);
	void (*emit_zone_text)(TracyCZoneCtx ctx, const char* txt, size_t size);
	void (*emit_zone_name)(TracyCZoneCtx ctx, const char* txt, size_t size);
	void (*emit_zone_color)(TracyCZoneCtx ctx, uint32_t color);
	void (*emit_zone_value)(TracyCZoneCtx ctx, uint64_t value);
	void (*emit_gpu_zone_begin)(const struct ___tracy_gpu_zone_begin_data);
	void (*emit_gpu_zone_begin_callstack)(const struct ___tracy_gpu_zone_begin_callstack_data);
	void (*emit_gpu_zone_begin_alloc)(const struct ___tracy_gpu_zone_begin_data);
	void (*emit_gpu_zone_begin_alloc_callstack)(const struct ___tracy_gpu_zone_begin_callstack_data);
	void (*emit_gpu_zone_end)(const struct ___tracy_gpu_zone_end_data data);
	void (*emit_gpu_time)(const struct ___tracy_gpu_time_data);
	void (*emit_gpu_new_context)(const struct ___tracy_gpu_new_context_data);
	void (*emit_gpu_context_name)(const struct ___tracy_gpu_context_name_data);
	void (*emit_gpu_calibration)(const struct ___tracy_gpu_calibration_data);
	void (*emit_gpu_time_sync)(const struct ___tracy_gpu_time_sync_data);
	void (*emit_gpu_zone_begin_serial)(const struct ___tracy_gpu_zone_begin_data);
	void (*emit_gpu_zone_begin_callstack_serial)(const struct ___tracy_gpu_zone_begin_callstack_data);
	void (*emit_gpu_zone_begin_alloc_serial)(const struct ___tracy_gpu_zone_begin_data);
	void (*emit_gpu_zone_begin_alloc_callstack_serial)(const struct ___tracy_gpu_zone_begin_callstack_data);
	void (*emit_gpu_zone_end_serial)(const struct ___tracy_gpu_zone_end_data data);
	void (*emit_gpu_time_serial)(const struct ___tracy_gpu_time_data);
	void (*emit_gpu_new_context_serial)(const struct ___tracy_gpu_new_context_data);
	void (*emit_gpu_context_name_serial)(const struct ___tracy_gpu_context_name_data);
	void (*emit_gpu_calibration_serial)(const struct ___tracy_gpu_calibration_data);
	void (*emit_gpu_time_sync_serial)(const struct ___tracy_gpu_time_sync_data);
	int32_t (*connected)(void);
	void (*emit_memory_alloc)(const void* ptr, size_t size, int32_t secure);
	void (*emit_memory_alloc_callstack)(const void* ptr, size_t size, int32_t depth, int32_t secure);
	void (*emit_memory_free)(const void* ptr, int32_t secure);
	void (*emit_memory_free_callstack)(const void* ptr, int32_t depth, int32_t secure);
	void (*emit_memory_alloc_named)(const void* ptr, size_t size, int32_t secure, const char* name);
	void (*emit_memory_alloc_callstack_named)(const void* ptr, size_t size, int32_t depth, int32_t secure, const char* name);
	void (*emit_memory_free_named)(const void* ptr, int32_t secure, const char* name);
	void (*emit_memory_free_callstack_named)(const void* ptr, int32_t depth, int32_t secure, const char* name);
	void (*emit_memory_discard)(const char* name, int32_t secure);
	void (*emit_memory_discard_callstack)(const char* name, int32_t secure, int32_t depth);
	void (*emit_message)(const char* txt, size_t size, int32_t callstack_depth);
	void (*emit_messageL)(const char* txt, int32_t callstack_depth);
	void (*emit_messageC)(const char* txt, size_t size, uint32_t color, int32_t callstack_depth);
	void (*emit_messageLC)(const char* txt, uint32_t color, int32_t callstack_depth);
	void (*emit_frame_mark)(const char* name);
	void (*emit_frame_mark_start)(const char* name);
	void (*emit_frame_mark_end)(const char* name);
	void (*emit_frame_image)(const void* image, uint16_t w, uint16_t h, uint8_t offset, int32_t flip);
	void (*emit_plot)(const char* name, double val);
	void (*emit_plot_float)(const char* name, float val);
	void (*emit_plot_int)(const char* name, int64_t val);
	void (*emit_plot_config)(const char* name, int32_t type, int32_t step, int32_t fill, uint32_t color);
	void (*emit_message_appinfo)(const char* txt, size_t size);
	struct __tracy_lockable_context_data* (*announce_lockable_ctx)(const struct ___tracy_source_location_data* srcloc);
	void (*terminate_lockable_ctx)(struct __tracy_lockable_context_data* lockdata);
	int32_t (*before_lock_lockable_ctx)(struct __tracy_lockable_context_data* lockdata);
	void (*after_lock_lockable_ctx)(struct __tracy_lockable_context_data* lockdata);
	void (*after_unlock_lockable_ctx)(struct __tracy_lockable_context_data* lockdata);
	void (*after_try_lock_lockable_ctx)(struct __tracy_lockable_context_data* lockdata, int32_t acquired);
	void (*mark_lockable_ctx)(struct __tracy_lockable_context_data* lockdata, const struct ___tracy_source_location_data* srcloc);
	void (*custom_name_lockable_ctx)(struct __tracy_lockable_context_data* lockdata, const char* name, size_t nameSz);
#ifdef TRACY_MANUAL_LIFETIME
	TRACY_API void (*startup_profiler)(void);
	TRACY_API void (*shutdown_profiler)(void);
	TRACY_API int32_t (*profiler_started)(void);
#endif
#ifdef TRACY_FIBERS
	TRACY_API void (*fiber_enter)(const char* fiber);
	TRACY_API void (*fiber_leave)(void);
#endif
#else
	void* m_Dummy;
#endif
} jx_tracy_api;

extern jx_tracy_api* tracy_api;

#ifndef TRACY_ENABLE
#define TracyCZone(c,x)
#define TracyCZoneN(c,x,y)
#define TracyCZoneC(c,x,y)
#define TracyCZoneNC(c,x,y,z)
#define TracyCZoneEnd(c)
#define TracyCZoneText(c,x,y)
#define TracyCZoneName(c,x,y)
#define TracyCZoneColor(c,x)
#define TracyCZoneValue(c,x)

#define TracyCAlloc(x,y)
#define TracyCFree(x)
#define TracyCSecureAlloc(x,y)
#define TracyCSecureFree(x)

#define TracyCAllocN(x,y,z)
#define TracyCFreeN(x,y)
#define TracyCSecureAllocN(x,y,z)
#define TracyCSecureFreeN(x,y)

#define TracyCFrameMark
#define TracyCFrameMarkNamed(x)
#define TracyCFrameMarkStart(x)
#define TracyCFrameMarkEnd(x)
#define TracyCFrameImage(x,y,z,w,a)

#define TracyCPlot(x,y)
#define TracyCPlotF(x,y)
#define TracyCPlotI(x,y)
#define TracyCPlotConfig(x,y,z,w,a)

#define TracyCMessage(x,y)
#define TracyCMessageL(x)
#define TracyCMessageC(x,y,z)
#define TracyCMessageLC(x,y)
#define TracyCAppInfo(x,y)

#define TracyCZoneS(x,y,z)
#define TracyCZoneNS(x,y,z,w)
#define TracyCZoneCS(x,y,z,w)
#define TracyCZoneNCS(x,y,z,w,a)

#define TracyCAllocS(x,y,z)
#define TracyCFreeS(x,y)
#define TracyCSecureAllocS(x,y,z)
#define TracyCSecureFreeS(x,y)

#define TracyCAllocNS(x,y,z,w)
#define TracyCFreeNS(x,y,z)
#define TracyCSecureAllocNS(x,y,z,w)
#define TracyCSecureFreeNS(x,y,z)

#define TracyCMessageS(x,y,z)
#define TracyCMessageLS(x,y)
#define TracyCMessageCS(x,y,z,w)
#define TracyCMessageLCS(x,y,z)

#define TracyCIsConnected 0

#ifdef TRACY_FIBERS
#  define TracyCFiberEnter(fiber)
#  define TracyCFiberLeave
#endif
#else
#undef TracyCSetThreadName
#undef TracyCZone
#undef TracyCZoneN
#undef TracyCZoneC
#undef TracyCZoneNC
#undef TracyCZoneEnd
#undef TracyCZoneText
#undef TracyCZoneName
#undef TracyCZoneColor
#undef TracyCZoneValue
#undef TracyCAlloc
#undef TracyCFree
#undef TracyCMemoryDiscard
#undef TracyCSecureAlloc
#undef TracyCSecureFree
#undef TracyCSecureMemoryDiscard
#undef TracyCAllocN
#undef TracyCFreeN
#undef TracyCSecureAllocN
#undef TracyCSecureFreeN
#undef TracyCFrameMark
#undef TracyCFrameMarkNamed
#undef TracyCFrameMarkStart
#undef TracyCFrameMarkEnd
#undef TracyCFrameImage
#undef TracyCPlot
#undef TracyCPlotF
#undef TracyCPlotI
#undef TracyCPlotConfig
#undef TracyCMessage
#undef TracyCMessageL
#undef TracyCMessageC
#undef TracyCMessageLC
#undef TracyCAppInfo
#undef TracyCZoneS
#undef TracyCZoneNS
#undef TracyCZoneCS
#undef TracyCZoneNCS
#undef TracyCAllocS
#undef TracyCFreeS
#undef TracyCMemoryDiscardS
#undef TracyCSecureAllocS
#undef TracyCSecureFreeS
#undef TracyCSecureMemoryDiscardS
#undef TracyCAllocNS
#undef TracyCFreeNS
#undef TracyCSecureAllocNS
#undef TracyCSecureFreeNS
#undef TracyCMessageS
#undef TracyCMessageLS
#undef TracyCMessageCS
#undef TracyCMessageLCS
#undef TracyCLockAnnounce
#undef TracyCLockTerminate
#undef TracyCLockBeforeLock
#undef TracyCLockAfterLock
#undef TracyCLockAfterUnlock
#undef TracyCLockAfterTryLock
#undef TracyCLockMark
#undef TracyCLockCustomName
#undef TracyCIsConnected
#ifdef TRACY_FIBERS
#  undef TracyCFiberEnter
#  undef TracyCFiberLeave
#endif

#define TracyCSetThreadName( name )                            tracy_api->set_thread_name( name );

#define TracyCZone( ctx, active )                              static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 };     TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#define TracyCZoneN( ctx, name, active )                       static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, 0 };     TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#define TracyCZoneC( ctx, color, active )                      static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#define TracyCZoneNC( ctx, name, color, active )               static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), TRACY_CALLSTACK, active );

#define TracyCZoneEnd( ctx )                                   tracy_api->emit_zone_end( ctx );

#define TracyCZoneText( ctx, txt, size )                       tracy_api->emit_zone_text( ctx, txt, size );
#define TracyCZoneName( ctx, txt, size )                       tracy_api->emit_zone_name( ctx, txt, size );
#define TracyCZoneColor( ctx, color )                          tracy_api->emit_zone_color( ctx, color );
#define TracyCZoneValue( ctx, value )                          tracy_api->emit_zone_value( ctx, value );

#define TracyCAlloc( ptr, size )                               tracy_api->emit_memory_alloc_callstack( ptr, size, TRACY_CALLSTACK, 0 )
#define TracyCFree( ptr )                                      tracy_api->emit_memory_free_callstack( ptr, TRACY_CALLSTACK, 0 )
#define TracyCMemoryDiscard( name )                            tracy_api->emit_memory_discard_callstack( name, 0, TRACY_CALLSTACK );
#define TracyCSecureAlloc( ptr, size )                         tracy_api->emit_memory_alloc_callstack( ptr, size, TRACY_CALLSTACK, 1 )
#define TracyCSecureFree( ptr )                                tracy_api->emit_memory_free_callstack( ptr, TRACY_CALLSTACK, 1 )
#define TracyCSecureMemoryDiscard( name )                      tracy_api->emit_memory_discard_callstack( name, 1, TRACY_CALLSTACK );

#define TracyCAllocN( ptr, size, name )                        tracy_api->emit_memory_alloc_callstack_named( ptr, size, TRACY_CALLSTACK, 0, name )
#define TracyCFreeN( ptr, name )                               tracy_api->emit_memory_free_callstack_named( ptr, TRACY_CALLSTACK, 0, name )
#define TracyCSecureAllocN( ptr, size, name )                  tracy_api->emit_memory_alloc_callstack_named( ptr, size, TRACY_CALLSTACK, 1, name )
#define TracyCSecureFreeN( ptr, name )                         tracy_api->emit_memory_free_callstack_named( ptr, TRACY_CALLSTACK, 1, name )

#define TracyCMessage( txt, size )                             tracy_api->emit_message( txt, size, TRACY_CALLSTACK );
#define TracyCMessageL( txt )                                  tracy_api->emit_messageL( txt, TRACY_CALLSTACK );
#define TracyCMessageC( txt, size, color )                     tracy_api->emit_messageC( txt, size, color, TRACY_CALLSTACK );
#define TracyCMessageLC( txt, color )                          tracy_api->emit_messageLC( txt, color, TRACY_CALLSTACK );

#define TracyCFrameMark                                        tracy_api->emit_frame_mark( 0 );
#define TracyCFrameMarkNamed( name )                           tracy_api->emit_frame_mark( name );
#define TracyCFrameMarkStart( name )                           tracy_api->emit_frame_mark_start( name );
#define TracyCFrameMarkEnd( name )                             tracy_api->emit_frame_mark_end( name );
#define TracyCFrameImage( image, width, height, offset, flip ) tracy_api->emit_frame_image( image, width, height, offset, flip );

#define TracyCPlot( name, val )                                tracy_api->emit_plot( name, val );
#define TracyCPlotF( name, val )                               tracy_api->emit_plot_float( name, val );
#define TracyCPlotI( name, val )                               tracy_api->emit_plot_int( name, val );
#define TracyCPlotConfig( name, type, step, fill, color )      tracy_api->emit_plot_config( name, type, step, fill, color );
#define TracyCAppInfo( txt, size )                             tracy_api->emit_message_appinfo( txt, size );

#define TracyCZoneS( ctx, depth, active )                      static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 };     TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), depth, active );
#define TracyCZoneNS( ctx, name, depth, active )               static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, 0 };     TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), depth, active );
#define TracyCZoneCS( ctx, color, depth, active )              static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), depth, active );
#define TracyCZoneNCS( ctx, name, color, depth, active )       static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = tracy_api->emit_zone_begin_callstack( &TracyConcat(___tracy_source_location,TracyLine), depth, active );

#define TracyCAllocS( ptr, size, depth )                       tracy_api->emit_memory_alloc_callstack( ptr, size, depth, 0 )
#define TracyCFreeS( ptr, depth )                              tracy_api->emit_memory_free_callstack( ptr, depth, 0 )
#define TracyCMemoryDiscardS( name, depth )                    tracy_api->emit_memory_discard_callstack( name, 0, depth )
#define TracyCSecureAllocS( ptr, size, depth )                 tracy_api->emit_memory_alloc_callstack( ptr, size, depth, 1 )
#define TracyCSecureFreeS( ptr, depth )                        tracy_api->emit_memory_free_callstack( ptr, depth, 1 )
#define TracyCSecureMemoryDiscardS( name, depth )              tracy_api->emit_memory_discard_callstack( name, 1, depth )

#define TracyCAllocNS( ptr, size, depth, name )                tracy_api->emit_memory_alloc_callstack_named( ptr, size, depth, 0, name )
#define TracyCFreeNS( ptr, depth, name )                       tracy_api->emit_memory_free_callstack_named( ptr, depth, 0, name )
#define TracyCSecureAllocNS( ptr, size, depth, name )          tracy_api->emit_memory_alloc_callstack_named( ptr, size, depth, 1, name )
#define TracyCSecureFreeNS( ptr, depth, name )                 tracy_api->emit_memory_free_callstack_named( ptr, depth, 1, name )

#define TracyCMessageS( txt, size, depth )                     tracy_api->emit_message( txt, size, depth );
#define TracyCMessageLS( txt, depth )                          tracy_api->emit_messageL( txt, depth );
#define TracyCMessageCS( txt, size, color, depth )             tracy_api->emit_messageC( txt, size, color, depth );
#define TracyCMessageLCS( txt, color, depth )                  tracy_api->emit_messageLC( txt, color, depth );

#define TracyCLockAnnounce( lock )                             static const struct ___tracy_source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; lock = tracy_api->announce_lockable_ctx( &TracyConcat(___tracy_source_location,TracyLine) );
#define TracyCLockTerminate( lock )                            tracy_api->terminate_lockable_ctx( lock );
#define TracyCLockBeforeLock( lock )                           tracy_api->before_lock_lockable_ctx( lock );
#define TracyCLockAfterLock( lock )                            tracy_api->after_lock_lockable_ctx( lock );
#define TracyCLockAfterUnlock( lock )                          tracy_api->after_unlock_lockable_ctx( lock );
#define TracyCLockAfterTryLock( lock, acquired )               tracy_api->after_try_lock_lockable_ctx( lock, acquired );
#define TracyCLockMark( lock )                                 static const struct tracy_api->source_location_data TracyConcat(___tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; tracy_api->mark_lockable_ctx( lock, &TracyConcat(___tracy_source_location,TracyLine) );
#define TracyCLockCustomName( lock, name, nameSz )             tracy_api->custom_name_lockable_ctx( lock, name, nameSz );

#define TracyCIsConnected                                      tracy_api->connected()

#ifdef TRACY_FIBERS
#  define TracyCFiberEnter( fiber ) tracy_api->fiber_enter( fiber );
#  define TracyCFiberLeave tracy_api->fiber_leave();
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif // JX_TRACY_H
