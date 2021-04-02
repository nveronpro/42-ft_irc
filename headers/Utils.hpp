/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <nveron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:30:24 by nveron            #+#    #+#             */
/*   Updated: 2021/03/22 13:36:28 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

//C headers
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <sys/socket.h> 
# include <stdlib.h> 
# include <netinet/in.h> 
# include <string.h> 
# include <time.h>
# include <sys/select.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <errno.h>

//C++ headers
# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <queue>
# include <stack>
# include <map>
# include <algorithm>
# include <exception>

//defines
//	text colors
# define RED "\033[0;31m"
# define CRED std::cout << "\033[0;31m"
# define GREEN "\033[0;92m"
# define CGREEN std::cout << "\033[0;92m"
# define MAG "\033[0;95m"
# define CMAG std::cout << "\033[0;95m"
# define CYAN "\033[0;96m"
# define CCYAN std::cout << "\033[0;96m"
# define BLUE "\033[0;94m"
# define CBLUE std::cout << "\033[0;94m"
# define YELLOW "\033[0;93m"
# define CYELLOW std::cout << "\033[0;93m"
# define GREY "\033[0;90m"
# define CGREY std::cout << "\033[0;90m"
# define END "\033[0m"
# define ENDL "\033[0m" << std::endl

#ifndef MAX_CHANNELS
# define MAX_CHANNELS 5
#endif

#ifndef MAX_TARGETS
# define MAX_TARGETS 3
#endif

#endif