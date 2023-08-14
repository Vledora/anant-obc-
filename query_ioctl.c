static int status = 1, dignity = 3, ego = 5;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmd,
    unsigned long arg)
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
#endif
{
    query_arg_t q;

    switch (cmd)
    {
        case QUERY_GET_VARIABLES:
            q.status = status;
            q.dignity = dignity;
            q.ego = ego;
            if (copy_to_user((query_arg_t *)arg, &q,
                sizeof(query_arg_t)))
            {
                return -EACCES;
            }
            break;
        case QUERY_CLR_VARIABLES:
            status = 0;
            dignity = 0;
            ego = 0;
            break;
        default:
            return -EINVAL;
    }

    return 0;
}