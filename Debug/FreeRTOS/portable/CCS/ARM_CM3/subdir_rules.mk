################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/CCS/ARM_CM3/port.obj: ../FreeRTOS/portable/CCS/ARM_CM3/port.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM3/port.d" --obj_directory="FreeRTOS/portable/CCS/ARM_CM3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/portable/CCS/ARM_CM3/portasm.obj: ../FreeRTOS/portable/CCS/ARM_CM3/portasm.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/uip" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/WebServer" --include_path="D:/Programme/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.7.LTS/include" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/driverlib" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/Source_App/LCD/inc" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3" --include_path="D:/work_ARM_LM3/FreeRTOS_LM3/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --display_error_number --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/CCS/ARM_CM3/portasm.d" --obj_directory="FreeRTOS/portable/CCS/ARM_CM3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


