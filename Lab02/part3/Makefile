CC=clang

copy:
	cp -f forkexit.c /usr/src/minix/servers/pm/forkexit.c

build: copy
	cd /usr/src && make build
	
shortbuild: copy
	cd /usr/src && make build MKUPDATE=yes

reboot: shortbuild
	reboot

sync:
	rsync -rvz -e 'ssh -p 2222' . root@10.240.119.104:/home/shubh/OSLab/Lab02/part3

reset:
	cd /usr/src && git stash && git checkout v3.3.0

clean: reset

make: reboot

.PHONY: clean