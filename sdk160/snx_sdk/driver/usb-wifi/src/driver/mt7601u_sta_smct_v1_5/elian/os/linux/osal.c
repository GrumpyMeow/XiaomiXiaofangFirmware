
#include "osal.h"

inline void* osal_memset(void *buf, int i, unsigned int len)
{
	return memset(buf, i, len);
}

inline void* osal_memcpy(void *dst, const void *src, unsigned int len)
{
	return memcpy(dst, src, len);
}

inline int osal_memcmp(const void *buf1, const void *buf2, unsigned int len)
{
	return memcmp(buf1, buf2, len);
}

inline int osal_timer_create(p_osal_timer ptimer)
{
	struct timer_list *timer = &ptimer->timer;
	init_timer(timer);
	timer->function = ptimer->timeoutHandler;
	timer->data = (unsigned long)ptimer->data;
	return 0;
}

inline int osal_timer_start(p_osal_timer ptimer, unsigned ms)
{
	struct timer_list *timer = &ptimer->timer;
	timer->expires = jiffies + (ms/(1000/HZ));
	add_timer(timer);
	return 0;
}

inline int osal_timer_stop(p_osal_timer ptimer)
{
	struct timer_list *timer = &ptimer->timer;
	del_timer(timer);
	return 0;
}

inline int osal_timer_modify(p_osal_timer ptimer, unsigned int ms)
{

	mod_timer(&ptimer->timer, jiffies + (ms)/(1000/HZ));
	return 0;
}

inline int osal_thread_create(p_osal_thread thread)
{
	thread->thread = kthread_create(thread->thread_func,
			thread->data,
			thread->name);
	if (NULL == thread->thread) {
		return -1;
	}
	return 0;
}

inline int osal_thread_run (p_osal_thread thread)
{
	if (thread->thread) {
		wake_up_process(thread->thread);
		return 0;
	}
	else {
		return -1;
	}
}
inline int osal_thread_stop (p_osal_thread thread)
{
	int ret;
	if ( (thread) && (thread->thread) ) {
		ret = kthread_stop(thread->thread);
		return ret;
	}
	return -1;
}


inline int osal_thread_should_stop (p_osal_thread thread)
{
	if ( (thread) && (thread->thread) ) {
		return kthread_should_stop();
	}
	else {
		return 1;
	}
}

inline int osal_msleep(unsigned int ms)
{
	msleep(ms);
	return 0;
}

inline unsigned int  osal_strlen(const char *str) 
{ 
	return strlen(str); 
} 

inline int osal_strcmp(const char *dst, const char *src) 
{ 
	return strcmp(dst, src); 
} 

inline int osal_strncmp(const char *dst, const char *src, unsigned int len) 
{ 
	return strncmp(dst, src, len); 
} 

inline char * osal_strcpy(char *dst, const char *src) 
{ 
	return strcpy(dst, src); 
} 
inline long int osal_strtol(const char *str, char **c, int adecimal)
{
	return simple_strtol(str, c, adecimal);
}
inline char *osal_strstr(const char *haystack, const char *needle)
{
	return strstr(haystack, needle);
}
inline int osal_lock_init(spinlock_t *l)
{
	//TODO:lock implenment depend on requirment.
	//spin_lock_init(l);
	return 0;
}
inline int osal_lock(spinlock_t *l)
{
	//TODO:lock implenment depend on requirment.
	//spin_lock(l);
	return 0;
}
inline int osal_unlock(spinlock_t *l)
{
	//TODO:lock implenment depend on requirment.
	//spin_unlock(l);
	return 0;
}

