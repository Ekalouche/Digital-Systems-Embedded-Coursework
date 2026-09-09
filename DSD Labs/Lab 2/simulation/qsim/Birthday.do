onerror {exit -code 1}
vlib work
vcom -work work Birthday.vho
vcom -work work Waveform.vwf.vht
vsim -c -t 1ps -L cyclonev -L altera -L altera_mf -L sgate -L altera_lnsim work.Birthday_vhd_vec_tst -voptargs=+acc
vcd file -direction Birthday.msim.vcd
vcd add -internal Birthday_vhd_vec_tst/*
vcd add -internal Birthday_vhd_vec_tst/i1/*
proc simTimestamp {} {
    echo "Simulation time: $::now ps"
    if { [string equal running [runStatus]] } {
        after 2500 simTimestamp
    }
}
after 2500 simTimestamp
run -all
quit -f

