################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
WebServer/emac.obj: ../WebServer/emac.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/emac.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/http-strings.obj: ../WebServer/http-strings.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/http-strings.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd-cgi.obj: ../WebServer/httpd-cgi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd-cgi.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd-fs.obj: ../WebServer/httpd-fs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd-fs.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/httpd.obj: ../WebServer/httpd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/httpd.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

WebServer/uIP_Task.obj: ../WebServer/uIP_Task.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="WebServer/uIP_Task.d_raw" --obj_directory="WebServer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


