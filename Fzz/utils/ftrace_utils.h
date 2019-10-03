#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_PATH 256
#define _STR(x) #x
#define STR(x) _STR(x)

int trace_fd;
int marker_fd;

static char *find_debugfs(void)
{
    static char debugfs[MAX_PATH+1];
    static int debugfs_found;
    char type[100];
    FILE *fp;

    if (debugfs_found)
	    return debugfs;

    if ((fp = fopen("/proc/mounts","r")) == NULL)
	    return NULL;

    while (fscanf(fp, "%*s %"
		  STR(MAX_PATH)
		  "s %99s %*s %*d %*d\n",
		  debugfs, type) == 2) {
	    if (strcmp(type, "debugfs") == 0)
		    break;
    }
    fclose(fp);

    if (strcmp(type, "debugfs") != 0)
	    return NULL;

    debugfs_found = 1;

    return debugfs;
}

void set_ftrace_pid()
{
	pid_t pid = getpid();
	char pid_buf[10];
	memset(pid_buf, '\0', 10);
	sprintf(pid_buf, "%u", pid);
	fprintf(stdout, "pid:%u\n", pid);
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/set_ftrace_pid");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, pid_buf, strlen(pid_buf));
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}

void set_function_fork()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/options/function-fork");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}

void clear_function_fork()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/options/function-fork");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "0", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}

void enable_trace_kmem_cache_free()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kmem_cache_free/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}
void enable_trace_kfree()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kfree/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}
void enable_trace_kmalloc()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kmalloc/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}
void enable_trace_kmem_cache_alloc_node()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kmem_cache_alloc_node/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}
void enable_trace_kmem_cache_alloc()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kmem_cache_alloc/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}
void enable_trace_kmalloc_node()
{
	char *debugfs;
	char path[2048]={0};
	int tmp_fd;
	debugfs = find_debugfs();
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/events/kmem/kmalloc_node/enable");
		tmp_fd = open(path, O_WRONLY);
		if(tmp_fd >= 0)
			write(tmp_fd, "1", 1);
		else{
			perror("open");
		}
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}

void init_marker_fd()
{
	char *debugfs;
	char path[2048]={0};
	debugfs = find_debugfs();
	printf("%s\n",debugfs);
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/tracing_on");
		trace_fd = open(path, O_WRONLY);
		if(trace_fd >= 0)
			write(trace_fd, "1", 1);

		strcpy(path, debugfs);
		strcat(path, "/tracing/trace_marker");
		marker_fd = open(path, O_WRONLY);
	}
	else{
		printf("Can not find debugfs :(");
	}
	return;
}

void write_marker_syscall_start(int idx){
	char marker[100]={0};
	sprintf(marker, "start calling syscall number: %d", idx);
	write(marker_fd, marker, strlen(marker));
	return;
}

void write_marker_syscall_end(int idx){
	char marker[100]={0};
	sprintf(marker, "finish calling syscall number: %d", idx);
	write(marker_fd, marker, strlen(marker));
	return;
}

void dump_ftrace_atexit(){
	char *debugfs;
	char path[2048] = {0};
	close(marker_fd);
	debugfs = find_debugfs();	
	printf("%s\n",debugfs);
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/tracing_on");
		trace_fd = open(path, O_WRONLY);
		if(trace_fd >=0 )
			write(trace_fd, "0", 1);
	}
	return;
}

void set_ftrace_buffer_size(){
	int tmp_fd;
	char *debugfs;
	char path[2048] = {0};
	debugfs = find_debugfs();	
	if(debugfs){
		strcpy(path, debugfs);
		strcat(path, "/tracing/buffer_size_kb");
		tmp_fd = open(path, O_WRONLY);
		if(trace_fd >=0 ){
			write(trace_fd, "50000", 5);
			close(tmp_fd);	
		}
		else{
			printf("failed to set buffer_size\n");
		}
	}
	return;

}
void set_dump_all_cpus(){
	int tmp_fd;
	char path[] = "/proc/sys/kernel/ftrace_dump_on_oops";
	tmp_fd = open(path, O_WRONLY);
	if(tmp_fd >= 0){
		if(write(tmp_fd, "1", 1) < 0)
			goto error;
	}
	else{
error:
		printf("failed to set ftrace_dump_on_oops");
	}
	return;
}
