################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
logic/acceleration.obj: ../logic/acceleration.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/acceleration.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/altitude.obj: ../logic/altitude.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/altitude.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/battery.obj: ../logic/battery.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/battery.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/bluerobin.obj: ../logic/bluerobin.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/bluerobin.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/clock.obj: ../logic/clock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/clock.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/datalog.obj: ../logic/datalog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/datalog.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/date.obj: ../logic/date.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/date.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/menu.obj: ../logic/menu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/menu.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/rfbsl.obj: ../logic/rfbsl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/rfbsl.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/rfsimpliciti.obj: ../logic/rfsimpliciti.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/rfsimpliciti.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/temperature.obj: ../logic/temperature.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/temperature.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

logic/user.obj: ../logic/user.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="C:\Users\igorg\workspace_v6_2\ez430_chronos_datalogger\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="C:/ti/ccs620/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccs620/ccsv6/tools/compiler/msp430_4.2.1/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/driver" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/include" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/logic" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/bluerobin" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Applications/application/End Device" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/drivers/code" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/bsp/mcus" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/radios/family5" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/mrfi/smartrf" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk" --include_path="C:/Users/igorg/workspace_v6_2/ez430_chronos_datalogger/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=ISM_LF --define=MRFI_CC430 --define=__CCE__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="logic/user.d" --obj_directory="logic" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

