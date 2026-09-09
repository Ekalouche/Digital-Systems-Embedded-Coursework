onerror {exit -code 1}
vlib work
vcom -work work Comp1Exam.vho
vcom -work work Waveform.vwf.vht
vsim -c -t 1ps -L cyclonev -L altera -L altera_mf -L sgate -L altera_lnsim work.Comp1Exam_vhd_vec_tst -voptargs=+acc
vcd file -direction Comp1Exam.msim.vcd
vcd add -internal Comp1Exam_vhd_vec_tst/*
vcd add -internal Comp1Exam_vhd_vec_tst/i1/*
proc simTimestamp {} {
    echo "Simulation time: $::now ps"
    if { [string equal running [runStatus]] } {
        after 2500 simTimestamp
    }
}
after 2500 simTimestamp
run -all
quit -f
