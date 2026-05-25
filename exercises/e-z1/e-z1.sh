sudo -i
man useradd
sudo useradd -m -d /home/testuser -s /bin/csh testuser
sudo passwd testuser

sudo userdel -r testuser
