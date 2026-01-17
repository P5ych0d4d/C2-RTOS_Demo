################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source_App/app_additional_funcs.obj: ../Source_App/app_additional_funcs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/app_additional_funcs.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/app_tasks.obj: ../Source_App/app_tasks.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/app_tasks.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/hw_api.obj: ../Source_App/hw_api.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/hw_api.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/main.obj: ../Source_App/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/main.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/ringbuf.obj: ../Source_App/ringbuf.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/ringbuf.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/startup_ccs.obj: ../Source_App/startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/startup_ccs.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/timertest.obj: ../Source_App/timertest.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/timertest.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/uartDrv.obj: ../Source_App/uartDrv.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/uartDrv.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source_App/ustdlib.obj: ../Source_App/ustdlib.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="Source_App/ustdlib.d" --obj_directory="Source_App" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


