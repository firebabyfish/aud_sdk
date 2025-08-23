ifeq ($(CODEC), floating)
LC3PLUS_DIR := $(ROOT_DIR)/middleware/lc3plus/floating_point

C_SOURCES += \
    $(LC3PLUS_DIR)/adjust_global_gain.c \
    $(LC3PLUS_DIR)/al_fec_fl.c \
    $(LC3PLUS_DIR)/apply_global_gain.c \
    $(LC3PLUS_DIR)/ari_codec.c \
    $(LC3PLUS_DIR)/attack_detector.c \
    $(LC3PLUS_DIR)/codec_exe.c \
    $(LC3PLUS_DIR)/constants.c \
    $(LC3PLUS_DIR)/cutoff_bandwidth.c \
    $(LC3PLUS_DIR)/dct4.c \
    $(LC3PLUS_DIR)/dec_entropy.c \
    $(LC3PLUS_DIR)/dec_lc3_fl.c \
    $(LC3PLUS_DIR)/detect_cutoff_warped.c \
    $(LC3PLUS_DIR)/enc_entropy.c \
    $(LC3PLUS_DIR)/enc_lc3_fl.c \
    $(LC3PLUS_DIR)/estimate_global_gain.c \
    $(LC3PLUS_DIR)/imdct.c \
    $(LC3PLUS_DIR)/lc3plus.c \
    $(LC3PLUS_DIR)/lc3plus_fft.c \
    $(LC3PLUS_DIR)/ltpf_coder.c \
    $(LC3PLUS_DIR)/ltpf_decoder.c \
    $(LC3PLUS_DIR)/mdct.c \
    $(LC3PLUS_DIR)/mdct_shaping.c \
    $(LC3PLUS_DIR)/near_nyquist_detector.c \
    $(LC3PLUS_DIR)/noise_factor.c \
    $(LC3PLUS_DIR)/noise_filling.c \
    $(LC3PLUS_DIR)/olpa.c \
    $(LC3PLUS_DIR)/pc_apply.c \
    $(LC3PLUS_DIR)/pc_classify.c \
    $(LC3PLUS_DIR)/pc_main.c \
    $(LC3PLUS_DIR)/pc_update.c \
    $(LC3PLUS_DIR)/per_band_energy.c \
    $(LC3PLUS_DIR)/plc_classify.c \
    $(LC3PLUS_DIR)/plc_compute_stab_fac.c \
    $(LC3PLUS_DIR)/plc_damping_scrambling.c \
    $(LC3PLUS_DIR)/plc_main.c \
    $(LC3PLUS_DIR)/plc_noise_substitution.c \
    $(LC3PLUS_DIR)/plc_noise_substitution0.c \
    $(LC3PLUS_DIR)/plc_phecu_f0_refine_first.c \
    $(LC3PLUS_DIR)/plc_phecu_fec_hq.c \
    $(LC3PLUS_DIR)/plc_phecu_hq_ecu.c \
    $(LC3PLUS_DIR)/plc_phecu_lf_peak_analysis.c \
    $(LC3PLUS_DIR)/plc_phecu_rec_frame.c \
    $(LC3PLUS_DIR)/plc_phecu_setf0hz.c \
    $(LC3PLUS_DIR)/plc_phecu_spec_ana.c \
    $(LC3PLUS_DIR)/plc_phecu_subst_spec.c \
    $(LC3PLUS_DIR)/plc_phecu_tba_per_band_gain.c \
    $(LC3PLUS_DIR)/plc_phecu_tba_spect_Xavg.c \
    $(LC3PLUS_DIR)/plc_phecu_tba_trans_dect_gains.c \
    $(LC3PLUS_DIR)/plc_phecu_trans_burst_ana_sub.c \
    $(LC3PLUS_DIR)/plc_tdc.c \
    $(LC3PLUS_DIR)/plc_tdc_tdac.c \
    $(LC3PLUS_DIR)/plc_update.c \
    $(LC3PLUS_DIR)/quantize_spec.c \
    $(LC3PLUS_DIR)/reorder_bitstream.c \
    $(LC3PLUS_DIR)/resamp12k8.c \
    $(LC3PLUS_DIR)/residual_coding.c \
    $(LC3PLUS_DIR)/residual_decoding.c \
    $(LC3PLUS_DIR)/setup_com_lc3plus.c \
    $(LC3PLUS_DIR)/setup_dec_lc3plus.c \
    $(LC3PLUS_DIR)/setup_enc_lc3plus.c \
    $(LC3PLUS_DIR)/sns_compute_scf.c \
    $(LC3PLUS_DIR)/sns_interpolate_scf.c \
    $(LC3PLUS_DIR)/sns_quantize_scf.c \
    $(LC3PLUS_DIR)/tns_coder.c \
    $(LC3PLUS_DIR)/tns_decoder.c
	
C_INCLUDES += -I$(LC3PLUS_DIR)
	
endif
