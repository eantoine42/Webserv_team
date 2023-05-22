#include <asm-generic/errno-base.h>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAX_EVENTS	2
#define BUFFER_SIZE	5

void	ft_read(int fd)
{
	char buffer[BUFFER_SIZE];
	int n;
	
	if ((n = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[n] = '\0';
		std::cout << buffer;
	}
	if (n == -1)
		perror("read");
}

void	ft_write(int fd)
{
	const char *str = "abcdcjhdsbjchvdjhsvcjdsvcjhdsvchjvdsjhcsdvc\n";
	size_t len = std::strlen(str);

	write(fd, str, len);
}

int main()
{
	struct epoll_event ev, events[MAX_EVENTS];
	int epollfd, pipe_fd[2], nfds;

	epollfd = epoll_create1(EPOLL_CLOEXEC);
	if (epollfd < 0) 
	{
		perror("epoll_create1");
		return EXIT_FAILURE;
	}

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return EXIT_FAILURE;
	}

	bzero(&ev, sizeof(struct epoll_event));
	ev.events = EPOLLIN;
	ev.data.fd = pipe_fd[0];

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, pipe_fd[0], &ev) < 0)
	{
		perror("epoll_ctl");
		return EXIT_FAILURE;
	}

	if (fork() == 0)
	{
		close(epollfd);
		close(pipe_fd[0]);
		ft_write(pipe_fd[1]);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[1]);


	while (true)
	{
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);	
		if (nfds < 0)
		{
			perror("epoll_wait");
			return EXIT_FAILURE;
		}

		for (int i = 0; i < nfds; i++)
		{
			switch (events[i].events)
			{
				case EPOLLIN | EPOLLHUP:
					std::cout << "Enter in EPOLLIN | EPOLLHUP case" << std::endl;
					ft_read(events[i].data.fd);
					break;
				case EPOLLIN:
					std::cout << "Enter in EPOLLIN case" << std::endl;
					ft_read(events[i].data.fd);
					break;
				case EPOLLHUP:
					std::cout << "EPOLLHUP" << std::endl;
					close(pipe_fd[0]);
					close(epollfd);
					exit(EXIT_SUCCESS);
					break;
				default:
					std::cout << "Default branch " << events[i].events << std::endl;
					exit(0);
			}
		}
	}

	return 0;
}
