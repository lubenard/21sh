# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    main.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 10:29:25 by lubenard          #+#    #+#              #
#    Updated: 2019/09/17 10:52:01 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo Which test should I run
echo 0: All of them
echo 1: Builtin test
echo 2: redirection test
echo 3: Exit the test and delete file if needed
echo Please enter valid number
read choice

if [ $choice -lt 3 ]
then
	make -C ..
fi

if [ $choice -eq 0 ]
then
	./builtin.sh
	./redirections.sh
fi

if [ $choice -eq 1 ]
then
	./builtin.sh
fi

if [ $choice -eq 2 ]
then
	./redirections.sh
fi

if [ $choice -eq 3 ]
then
	echo Exiting..
	rm -f compare* file* auteur
	exit
fi
