TEMPLATE = subdirs

SUBDIRS = \
    src/general \ 
	src/app

src/app.depends = src/general
