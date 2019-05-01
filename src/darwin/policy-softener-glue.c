#include "frida-helper-backend.h"

#ifdef HAVE_IOS
#include <mach/mach.h>
#endif

extern kern_return_t bootstrap_look_up (mach_port_t  bootstrap_port, char * service_name, mach_port_t* service_port);
typedef int (* JbdCallFunc) (guint32 service_port, guint command, guint pid);

guint32
_frida_electra_policy_softener_internal_jb_connect ()
{
#ifdef HAVE_IOS
  mach_port_t service_port = MACH_PORT_NULL;
  kern_return_t kr;

  kr = bootstrap_look_up (bootstrap_port, "org.coolstar.jailbreakd", &service_port);
  if (kr != KERN_SUCCESS)
    return MACH_PORT_NULL;

  return service_port;
#else
  return 0;
#endif
}

void
_frida_electra_policy_softener_internal_jb_disconnect (guint32 service_port)
{
#ifdef HAVE_IOS
  mach_port_t self_task;

  self_task = mach_task_self ();
  mach_port_deallocate (self_task, service_port);
#endif
}

gint
_frida_electra_policy_softener_internal_jb_entitle_now (void * jbd_call, guint32 service_port, guint pid)
{
#ifdef HAVE_IOS
  JbdCallFunc jbd_call_func = (JbdCallFunc) jbd_call;

  return jbd_call_func (service_port, 1, pid);
#else
  return 0;
#endif
}
