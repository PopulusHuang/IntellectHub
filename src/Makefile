
DIR = check_session dev_manage device_list login sheet_show show_dev switch temperature_sheet timer_sheet_submit
all:
	@for i in $(DIR);do make -C $$i/;done
clean:
	@for i in $(DIR); do make cleanall -C $$i/; done
cleanobj:
	@for i in $(DIR); do make cleanobj -C $$i/; done
