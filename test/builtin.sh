# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtin.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 10:37:05 by lubenard          #+#    #+#              #
#    Updated: 2019/09/17 12:27:04 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

../21sh 'cd; cd /Users; cd ahah; cd /Users ~/; cd -;cd --; cd ~/;cd ~truc;cd ~/luca; cd /Users/lubenard;'

printf "\033[1;35mALL UNIT TEST ABOUT CD HAVE BEEN DONE, PRESS ANY KEY TO LAUNCH NEXT TESTS\033[0m"
read $wait

../21sh 'setenv; setenv TEST=truc; setenv TEST2=truc TEST3=machin; setenv truc= machin; setenv ~truc=machin;env'

printf "\033[1;35mALL UNIT TEST ABOUT SETENV HAVE BEEN DONE, PRESS ANY KEY TO LAUNCH NEXT TESTS\033[0m"
read $wait

#../21sh 'cd; cd /Users; cd ahah; cd -;cd --; cd ~/;cd ~truc;cd ~/luca; cd /Users/lubenard; cd '

#read $wait

#../21sh 'cd; cd /Users; cd ahah; cd -;cd --; cd ~/;cd ~truc;cd ~/luca; cd /Users/lubenard; cd '

#read $wait

#../21sh 'cd; cd /Users; cd ahah; cd -;cd --; cd ~/;cd ~truc;cd ~/luca; cd /Users/lubenard; cd '
