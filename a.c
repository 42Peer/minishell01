char *
readline(const char *p)
{
	HistEvent ev;
	const char * volatile prompt = p;
	int count;
	const char *ret;
	char *buf;
	static int used_event_hook;
	if (e == NULL || h == NULL)
		rl_initialize();
	if (rl_did_startup_hook == 0 && rl_startup_hook) {
		rl_did_startup_hook = 1;
		(*rl_startup_hook)(NULL, 0);
	}
	tty_init(e);
	rl_done = 0;
	(void)setjmp(topbuf);
	buf = NULL;
	/* update prompt accordingly to what has been passed */
	if (rl_set_prompt(prompt) == -1)
		goto out;
	if (rl_pre_input_hook)
		(*rl_pre_input_hook)(NULL, 0);
	if (rl_event_hook && !(e->el_flags & NO_TTY)) {
		el_set(e, EL_GETCFN, _rl_event_read_char);
		used_event_hook = 1;
	}
	if (!rl_event_hook && used_event_hook) {
		el_set(e, EL_GETCFN, EL_BUILTIN_GETCFN);
		used_event_hook = 0;
	}
	rl_already_prompted = 0;
	/* get one line from input stream */
	ret = el_gets(e, &count);
	if (ret && count > 0) {
		int lastidx;
		buf = strdup(ret);
		if (buf == NULL)
			goto out;
		lastidx = count - 1;
		if (buf[lastidx] == '\n')
			buf[lastidx] = '\0';
	} else
		buf = NULL;
	history(h, &ev, H_GETSIZE);
	history_length = ev.num;
out:
	tty_end(e, TCSADRAIN);
	return buf;
}
//android.googlesource.com


/*
char *
readline(char *buffer,int buffer_size)
{
	int ix = 0, bytes_malloced = 0;

	if (!buffer)
	{
		bytes_malloced = 64;
		buffer = (char *)malloc(bytes_malloced);//
		buffer_size = bytes_malloced;
	}
	for (;;++ix)
	{
		int ch;

		if (ix == buffer_size - 1)
		{
			if (!bytes_malloced)
				break;
			bytes_malloced += bytes_malloced;
			buffer = (char *)realloc(buffer, bytes_malloced);//
			buffer_size = bytes_malloced;
		}
		ch = getchar();
		if (ch == EOF)
		{
			if (bytes_malloced)
				free(buffer);
			return NULL;
		}
		if (ch =='\n')
			break;
		buffer[ix] = ch;
	}
	// 0 terminate buffer.
	buffer[ix] ='\0';
	return buffer;
}
opensource.apple.com
*/