################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./driver/as.obj" \
"./driver/bmp_as.obj" \
"./driver/bmp_ps.obj" \
"./driver/buzzer.obj" \
"./driver/cma_as.obj" \
"./driver/cma_ps.obj" \
"./driver/ports.obj" \
"./driver/ps.obj" \
"./driver/radio.obj" \
"./driver/rf1a.obj" \
"./driver/timer.obj" \
"./logic/acceleration.obj" \
"./logic/altitude.obj" \
"./logic/battery.obj" \
"./logic/bluerobin.obj" \
"./logic/clock.obj" \
"./logic/datalog.obj" \
"./logic/date.obj" \
"./logic/menu.obj" \
"./logic/rfbsl.obj" \
"./logic/rfsimpliciti.obj" \
"./logic/temperature.obj" \
"./logic/user.obj" \
"./simpliciti/Applications/application/End Device/main_ED_BM.obj" \
"../lnk_cc430f6137.cmd" \
"../bluerobin/BlueRobin_RX_915MHz.lib" \
"../driver/ez430_chronos_datalogger_drivers.lib" \
"../simpliciti/CC430_End_Device_915MHz.lib" \
$(GEN_CMDS__FLAG) \
-lrts430x.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include bluerobin/subdir_vars.mk
-include driver/subdir_vars.mk
-include logic/subdir_vars.mk
-include simpliciti/Applications/application/End\ Device/subdir_vars.mk
-include simpliciti/subdir_vars.mk
-include subdir_rules.mk
-include bluerobin/subdir_rules.mk
-include driver/subdir_rules.mk
-include logic/subdir_rules.mk
-include simpliciti/Applications/application/End\ Device/subdir_rules.mk
-include simpliciti/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ez430_chronos_datalogger_915MHz.out \

EXE_OUTPUTS__QUOTED += \
"ez430_chronos_datalogger_915MHz.out" \


# All Target
all: ez430_chronos_datalogger_915MHz.out

# Tool invocations
ez430_chronos_datalogger_915MHz.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 -g --define=__CC430F6137__ --define=ISM_US --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal -z -m"ez430_chronos_datalogger_915MHz.map" --heap_size=80 --stack_size=80 --use_hw_mpy=F5 -i"C:/ti/ccs620/ccsv6/ccs_base/msp430/include" -i"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/lib" -i"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" -i"C:/ti/ccs620/ccsv6/ccs_base/msp430/lib" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="ez430_chronos_datalogger_915MHz_linkInfo.xml" --rom_model -o "ez430_chronos_datalogger_915MHz.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.d" "driver\as.d" "driver\bmp_as.d" "driver\bmp_ps.d" "driver\buzzer.d" "driver\cma_as.d" "driver\cma_ps.d" "driver\ports.d" "driver\ps.d" "driver\radio.d" "driver\rf1a.d" "driver\timer.d" "logic\acceleration.d" "logic\altitude.d" "logic\battery.d" "logic\bluerobin.d" "logic\clock.d" "logic\datalog.d" "logic\date.d" "logic\menu.d" "logic\rfbsl.d" "logic\rfsimpliciti.d" "logic\temperature.d" "logic\user.d" "simpliciti\Applications\application\End Device\main_ED_BM.d" 
	-$(RM) "main.obj" "driver\as.obj" "driver\bmp_as.obj" "driver\bmp_ps.obj" "driver\buzzer.obj" "driver\cma_as.obj" "driver\cma_ps.obj" "driver\ports.obj" "driver\ps.obj" "driver\radio.obj" "driver\rf1a.obj" "driver\timer.obj" "logic\acceleration.obj" "logic\altitude.obj" "logic\battery.obj" "logic\bluerobin.obj" "logic\clock.obj" "logic\datalog.obj" "logic\date.obj" "logic\menu.obj" "logic\rfbsl.obj" "logic\rfsimpliciti.obj" "logic\temperature.obj" "logic\user.obj" "simpliciti\Applications\application\End Device\main_ED_BM.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/hex430.exe" --ti_txt "ez430_chronos_datalogger_915MHz.out" -o "ez430_chronos_datalogger_915MHz.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

