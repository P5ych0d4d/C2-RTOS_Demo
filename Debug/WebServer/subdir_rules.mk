################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
WebServer/emac.obj: ../WebServer/emac.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/emac.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/http-strings.obj: ../WebServer/http-strings.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/http-strings.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd-cgi.obj: ../WebServer/httpd-cgi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd-cgi.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd-fs.obj: ../WebServer/httpd-fs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd-fs.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd.obj: ../WebServer/httpd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/uIP_Task.obj: ../WebServer/uIP_Task.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/uIP_Task.d" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


