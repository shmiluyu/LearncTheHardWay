#include "shell.h"
#include "debug.h"
#include <stdarg.h>

int shell_exec(Shell template,...)
{
	apr_pool_t *p = NULL;
	int rc = -1;
	apr_status_t rv = APR_SUCCESS;
	va_list argp;
	const char *key = NULL;
	const char *arg = NULL;
	int i = 0;

	rv = apr_pool_create(&p,NULL);
	check(rv == APR_SUCCESS,"Failed to create pool");

	va_start(argp,template);
	for(key = va_arg(argp,const char *);
		key!=NULL;
		key = va_arg(argp,const char *))
	{
		arg = va_arg(argp,const char *);

		for(i = 0; template.args[i]!=NULL;i++){
			if(strcmp(template.args[i],key)==0){
				template.args[i] = arg;
				break;
			}
		}
	}

	rc = Shell_run(p,&template);
	apr_pool_destory(p);
	va_end(argp);
	return rc;
error:
	if(p)apr_pool_destory(p);
	return rc;
}

int Shell_run(apr_pool_t *p,Shell *cmd)
{
	apr_procattr_t *attr;
	apr_status_t rv;
	apr_proc_t newproc;
	//进程属性设置
	rv = apr_procattr_create(&attr,p);
	check(rv == APR_SUCCESS,"Failed to create proc attr.");
	//设置子进程的io,APR_NO_PIPE,则继承父进程
	rv = apr_procattr_io_set(attr,APR_NO_PIPE,APR_NO_PIPE,
		APR_NO_PIPE);
	check(rv == APR_SUCCESS,"Failed to set IO of command.");
	//设置子进程的执行根目录
	rv = apr_procattr_dir_set(attr,cmd->dir);
	check(rv == APR_SUCCESS,"Failed to set root to %s.",cmd->dir);
	//设置子进程调用的命令类型
	// APR_SHELLCMD     –  Anything that the shell can handle
	// APR_PROGRAM      –  Executable program   (default) 
	// APR_PROGRAM_ENV  –  Executable program, copy environment
	// APR_PROGRAM_PATH –  Executable program on PATH, copy env
	rv = apr_procattr_cmdtype_set(attr,APR_PROGRAM_PATH);
	check(rv == APR_SUCCESS,"Failed to set cmd type.");
	//运行
	rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
	check(rv == APR_SUCCESS, "Failed to run command.");
	//等待运行结束
	rv = apr_proc_wait(&newproc,&cmd->exit_code,&cmd->exit_why,APR_WAIT);
	check(rv == APR_CHILD_DONE,"Failed to wait.");
	// exitwhy	Why the child died, the bitwise or of:
	// APR_PROC_EXIT         -- process terminated normally
	// APR_PROC_SIGNAL       -- process was killed by a signal
	// APR_PROC_SIGNAL_CORE  -- process was killed by a signal, and generated a core dump.
	check(cmd->exit_code==0,"%s exit badly.",cmd->exe);
	check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed",cmd->exe);
	return 0;

error:
	return -1;
}

Shell CLEANUP_SH = {
	.exe = "rm",
	.dir = "/tmp",
	.args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz","/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL}
};

Shell GIT_SH = {
	.dir = "/tmp",
	.exe = "git",
	.args = {"git", "clone", "URL", "pkg-build", NULL}
};

Shell TAR_SH = {
	.dir = "/tmp/pkg-build",
	.exe = "tar",
	.args = {"tar", "-xzf", "FILE", "--strip-components", "1", NULL}
};

Shell CURL_SH = {
	.dir = "/tmp",
	.exe = "curl",
	.args = {"curl", "-L", "-o", "TARGET", "URL", NULL}
};

Shell CONFIGURE_SH = {
	.exe = "./configure",
	.dir = "/tmp/pkg-build",
	.args = {"configure", "OPTS", NULL},
};

Shell MAKE_SH = {
	.exe = "make",
	.dir = "/tmp/pkg-build",
	.args = {"make", "OPTS", NULL}
};

Shell INSTALL_SH = {
	.exe = "sudo",
	.dir = "/tmp/pkg-build",
	.args = {"sudo", "make", "TARGET", NULL}
};