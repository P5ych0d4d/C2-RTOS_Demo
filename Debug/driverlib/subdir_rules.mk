################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driverlib/adc.obj: ../driverlib/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/adc.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/can.obj: ../driverlib/can.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/can.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/comp.obj: ../driverlib/comp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/comp.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/cpu.obj: ../driverlib/cpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/cpu.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/epi.obj: ../driverlib/epi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/epi.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/ethernet.obj: ../driverlib/ethernet.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/ethernet.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/flash.obj: ../driverlib/flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/flash.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/gpio.obj: ../driverlib/gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/gpio.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/hibernate.obj: ../driverlib/hibernate.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/hibernate.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/i2c.obj: ../driverlib/i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/i2c.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/i2s.obj: ../driverlib/i2s.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/i2s.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/interrupt.obj: ../driverlib/interrupt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/interrupt.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/mpu.obj: ../driverlib/mpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/mpu.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/pwm.obj: ../driverlib/pwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/pwm.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/qei.obj: ../driverlib/qei.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/qei.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/ssi.obj: ../driverlib/ssi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/ssi.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/sysctl.obj: ../driverlib/sysctl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/sysctl.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/systick.obj: ../driverlib/systick.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/systick.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/timer.obj: ../driverlib/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/timer.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/uart.obj: ../driverlib/uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/uart.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/udma.obj: ../driverlib/udma.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/udma.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/usb.obj: ../driverlib/usb.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/usb.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driverlib/watchdog.obj: ../driverlib/watchdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driverlib/watchdog.d_raw" --obj_directory="driverlib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


