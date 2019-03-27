
#include "minishell.h"

void ft_perror(char *str)
{
	int	len;

	if (errno_f)
	{
		len = ft_strlen(str);
		write(2, str, len);
		if (errno_f >= EPERM && errno_f <= EPIPE)
			pr_gen_perror();
		else if (errno_f >= EDOM && errno_f <= ERANGE)
			pr_ms_perror();
		else if (errno_f >= EAGAIN && errno_f <= EALREADY)
			pr_nonb_perror();
		else if (errno_f >= ENOTSOCK && errno_f <= EADDRNOTAVAIL)
			pr_ns_arg_err_perror();
		else if (errno_f >= ENETDOWN && errno_f <= ENAMETOOLONG)
			pr_ns_op_err_perror();
		else if (errno_f >= EHOSTDOWN && errno_f <= ENOTEMPTY)
			pr_rearr_perror();
		else if (errno_f >= EPROCLIM && errno_f <= EDQUOT)
			pr_qm_perror();
		else if (errno_f >= ESTALE && errno_f <= ENEEDAUTH)
			pr_nfs_perror();
		else if (errno_f >= EPWROFF && errno_f <= ELAST)
			pr_ide_perror();
		errno_f = 0;
	}
}

void pr_gen_perror(void)
{
	int err;
	char *str[] = {
			": Operation not permitted",
			": No such file or directory",
			": No such process",
			": Interrupted system call",
			": Input/output error",
			": Device not configured",
			": Argument list too long",
			": Exec format error",
			": Bad file descriptor",
			": No child processes",
			": Resource deadlock avoided",
			": Cannot allocate memory",
			": Permission denied",
			": Bad address",
			": Block device required",
			": Device / Resource busy",
			": File exists",
			": Cross-device link",
			": Operation not supported by device",
			": Not a directory",
			": Is a directory",
			": Invalid argument",
			": Too many open files in system",
			": Too many open files",
			": Inappropriate ioctl for device",
			": Text file busy",
			": File too large",
			": No space left on device",
			": Illegal seek",
			": Read-only file system",
			": Too many links",
			": Broken pipe"
	};
	err = -1;
	if (errno_f == EPERM)
		err += EPERM;
	else if (errno_f == ENOENT)
		err += ENOENT;
	else if (errno_f == ESRCH)
		err += ESRCH;
	else if (errno_f == EINTR)
		err += EINTR;
	else if (errno_f == EIO)
		err += EIO;
	else if (errno_f == ENXIO)
		err += ENXIO;
	else if (errno_f == E2BIG)
		err += E2BIG;
	else if (errno_f == ENOEXEC)
		err += ENOEXEC;
	else if (errno_f == EBADF)
		err += EBADF;
	else if (errno_f == ECHILD)
		err += ECHILD;
	else if (errno_f == EDEADLK)
		err += EDEADLK;
	else if (errno_f == ENOMEM)
		err += ENOMEM;
	else if (errno_f == EACCES)
		err += EACCES;
	else if (errno_f == EFAULT)
		err += EFAULT;
	else if (errno_f == ENOTBLK)
		err += ENOTBLK;
	else if (errno_f == EBUSY)
		err += EBUSY;
	else if (errno_f == EEXIST)
		err += EEXIST;
	else if (errno_f == EXDEV)
		err += EXDEV;
	else if (errno_f == ENODEV)
		err += ENODEV;
	else if (errno_f == ENOTDIR)
		err += ENOTDIR;
	else if (errno_f == EISDIR)
		err += EISDIR;
	else if (errno_f == EINVAL)
		err += EINVAL;
	else if (errno_f == ENFILE)
		err += ENFILE;
	else if (errno_f == EMFILE)
		err += EMFILE;
	else if (errno_f == ENOTTY)
		err += ENOTTY;
	else if (errno_f == ETXTBSY)
		err += ETXTBSY;
	else if (errno_f == EFBIG)
		err += EFBIG;
	else if (errno_f == ENOSPC)
		err += ENOSPC;
	else if (errno_f == ESPIPE)
		err += ESPIPE;
	else if (errno_f == EROFS)
		err += EROFS;
	else if (errno_f == EMLINK)
		err += EMLINK;
	else
		err += EPIPE;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_ms_perror(void)
{
	int err;
	char *str[] = {
			": Numerical argument out of domain",
			": Result too large"
	};
	err = -33;
	if (errno_f == EDOM)
		err += EDOM;
	else
		err += ERANGE;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_nonb_perror(void)
{
	int err;
	char *str[] = {
			": Resource temporarily unavailable",
			": Operation now in progress",
			": Operation already in progress"
	};
	err = -35;
	if (errno_f == EAGAIN)
		err += EAGAIN;
	else if (errno_f == EINPROGRESS)
		err += EINPROGRESS;
	else
		err += EALREADY;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_ns_arg_err_perror(void)
{
	int err;
	char *str[] = {
			": Socket operation on non-socket",
			": Destination address required",
			": Message too long",
			": Protocol wrong type for socket",
			": Protocol not available",
			": Protocol not supported",
			": Socket type not supported",
			": Operation not supported",
			": Protocol family not supported",
			": Address family not supported by protocol family",
			": Address already in use",
			": Can't assign requested address"
	};
	err = -38;
	if (errno_f == ENOTSOCK)
		err += ENOTSOCK;
	else if (errno_f == EDESTADDRREQ)
		err += EDESTADDRREQ;
	else if (errno_f == EMSGSIZE)
		err += EMSGSIZE;
	else if (errno_f == EPROTOTYPE)
		err += EPROTOTYPE;
	else if (errno_f == ENOPROTOOPT)
		err += ENOPROTOOPT;
	else if (errno_f == EPROTONOSUPPORT)
		err += EPROTONOSUPPORT;
	else if (errno_f == ESOCKTNOSUPPORT)
		err += ESOCKTNOSUPPORT;
	else if (errno_f == ENOTCONNENOTSUP)
		err += ENOTCONNENOTSUP;
	else if (errno_f == EPFNOSUPPORT)
		err += EPFNOSUPPORT;
	else if (errno_f == EAFNOSUPPORT)
		err += EAFNOSUPPORT;
	else if (errno_f == EADDRINUSE)
		err += EADDRINUSE;
	else
		err += EADDRNOTAVAIL;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_ns_op_err_perror(void)
{
	int err;
	char *str[] = {
			": Network is down",
			": Network is unreachable",
			": Network dropped connection on reset",
			": Software caused connection abort",
			": Connection reset by peer",
			": No buffer space available",
			": Socket is already connected",
			": Socket is not connected",
			": Can't send after socket shutdown",
			": Too many references: can't splice",
			": Operation timed out",
			": Connection refused",
			": Too many levels of symbolic links",
			": File name too long"
	};
	err = -50;
	if (errno_f == ENETDOWN)
		err += ENETDOWN;
	else if (errno_f == ENETUNREACH)
		err += ENETUNREACH;
	else if (errno_f == ENETRESET)
		err += ENETRESET;
	else if (errno_f == ECONNABORTED)
		err += ECONNABORTED;
	else if (errno_f == ECONNRESET)
		err += ECONNRESET;
	else if (errno_f == ENOBUFS)
		err += ENOBUFS;
	else if (errno_f == EISCONN)
		err += EISCONN;
	else if (errno_f == ENOTCONN)
		err += ENOTCONN;
	else if (errno_f == ESHUTDOWN)
		err += ESHUTDOWN;
	else if (errno_f == ETOOMANYREFS)
		err += ETOOMANYREFS;
	else if (errno_f == ETIMEDOUT)
		err += ETIMEDOUT;
	else if (errno_f == ECONNREFUSED)
		err += ECONNREFUSED;
	else if (errno_f == ELOOP)
		err += ELOOP;
	else
		err += ENAMETOOLONG;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_rearr_perror(void)
{
	int err;
	char *str[] = {
			": Host is down",
			": No route to host",
			": Directory not empty"
	};
	err = -64;
	if (errno_f == EHOSTDOWN)
		err += EHOSTDOWN;
	if (errno_f == EHOSTUNREACH)
		err += EHOSTUNREACH;
	else
		err += ENOTEMPTY;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_qm_perror(void)
{
	int err;
	char *str[] = {
			": Too many processes",
			": Too many users",
			": Disc quota exceeded"
	};
	err = -67;
	if (errno_f == EPROCLIM)
		err += EPROCLIM;
	if (errno_f == EUSERS)
		err += EUSERS;
	else
		err += EDQUOT;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_nfs_perror(void)
{
	int err;
	char *str[] = {
			": Stale NFS file handle",
			": Too many levels of remote in path",
			": RPC struct is bad",
			": RPC version wrong",
			": RPC prog. not avail",
			": Program version wrong",
			": Bad procedure for program",
			": No locks available",
			": Function not implemented",
			": Inappropriate file type or format",
			": Authentication error",
			": Need authenticator"
	};
	err = -70;
	if (errno_f == ESTALE)
		err += ESTALE;
	else if (errno_f == EREMOTE)
		err += EREMOTE;
	else if (errno_f == EBADRPC)
		err += EBADRPC;
	else if (errno_f == ERPCMISMATCH)
		err += ERPCMISMATCH;
	else if (errno_f == EPROGUNAVAIL)
		err += EPROGUNAVAIL;
	else if (errno_f == EPROGMISMATCH)
		err += EPROGMISMATCH;
	else if (errno_f == EPROCUNAVAIL)
		err += EPROCUNAVAIL;
	else if (errno_f == ENOLCK)
		err += ENOLCK;
	else if (errno_f == ENOSYS)
		err += ENOSYS;
	else if (errno_f == EFTYPE)
		err += EFTYPE;
	else if (errno_f == EAUTH)
		err += EAUTH;
	else
		err += ENEEDAUTH;
	write(2, str[err], ft_strlen(str[err]));
}

void pr_ide_perror(void)
{
	int err;
	char *str[] = {
			": Device power is off",
			": Device error, e.g. paper out",
			": Value too large to be stored in data type",
			": Bad executable",
			": Bad CPU type in executable",
			": Shared library version mismatch",
			": Malformed Macho file",
			": Operation canceled",
			": Identifier removed",
			": No message of desired type",
			": Illegal byte sequence",
			": Attribute not found",
			": Bad message",
			": Reserved",
			": No message available on STREAM",
			": Reserved",
			": No STREAM resources",
			": Not a STREAM",
			": Protocol error",
			": STREAM ioctl timeout",
			": Operation not supported on socket",
			": No such policy registered",
			": Interface output queue is full",
			": Must be equal largest errno"
	};
	err = -82;
	if (errno_f == EPWROFF)
		err += EPWROFF;
	else if (errno_f == EDEVERR)
		err += EDEVERR;
	else if (errno_f == EOVERFLOW)
		err += EOVERFLOW;
	else if (errno_f == EBADEXEC)
		err += EBADEXEC;
	else if (errno_f == EBADARCH)
		err += EBADARCH;
	else if (errno_f == ESHLIBVERS)
		err += ESHLIBVERS;
	else if (errno_f == EBADMACHO)
		err += EBADMACHO;
	else if (errno_f == ECANCELED)
		err += ECANCELED;
	else if (errno_f == EIDRM)
		err += EIDRM;
	else if (errno_f == ENOMSG)
		err += ENOMSG;
	else if (errno_f == EILSEQ)
		err += EILSEQ;
	else if (errno_f == ENOATTR)
		err += ENOATTR;
	else if (errno_f == EBADMSG)
		err += EBADMSG;
	else if (errno_f == EMULTIHOP)
		err += EMULTIHOP;
	else if (errno_f == ENODATA)
		err += ENODATA;
	else if (errno_f == ENOLINK)
		err += ENOLINK;
	else if (errno_f == ENOSR)
		err += ENOSR;
	else if (errno_f == ENOSTR)
		err += ENOSTR;
	else if (errno_f == EPROTO)
		err += EPROTO;
	else if (errno_f == ETIME)
		err += ETIME;
	else if (errno_f == EOPNOTSUPP)
		err += EOPNOTSUPP;
	else if (errno_f == ENOPOLICY)
		err += ENOPOLICY;
	else if (errno_f == EQFULL)
		err += EQFULL;
	else
		err += ELAST;
	write(2, str[err], ft_strlen(str[err]));
}