if [ $1 = "local" ]
then
	echo "Syncing with local"
	rsync -rvz -e 'ssh -p 2222' . root@127.0.0.0:/home/shubh/OSLab
else
	echo "Syncing with remote"
	rsync -rvz -e 'ssh -p 2222' . root@10.240.119.104:/home/shubh/OSLab
fi

