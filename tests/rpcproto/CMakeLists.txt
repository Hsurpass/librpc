cmake_minimum_required(VERSION 3.5)

project(rpcproto)


# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(Protobuf REQUIRED COMPONENTS protobuf)
#FIND_PACKAGE(Protobuf REQUIRED CONFIG COMPONENTS protobuf)
MESSAGE(STATUS "Protobuf_FOUND:" ${Protobuf_FOUND})
MESSAGE(STATUS "Protobuf_VERSION:" ${Protobuf_VERSION})
message("Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
message("Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
message("Protobuf_PROTOC_LIBRARIES: " ${Protobuf_PROTOC_LIBRARIES})
message("Protobuf_LITE_LIBRARIES: " ${Protobuf_LITE_LIBRARIES})

# find_package(absl REQUIRED CONFIG)

include_directories(/usr/local/include/absl)

add_executable(rpcproto main.cpp rpc.pb.cc)
target_link_libraries(rpcproto 
    pthread
    # ssl crypto 
    # boost_thread
    ${Protobuf_LIBRARIES} 
    # ${Protobuf_LITE_LIBRARIES}
    # ${Protobuf_PROTOC_LIBRARIES}
    # gmock
    # GMock::GMock
    # absl::base absl::strings absl::synchronization absl::time
    # absl_bad_any_cast_impl
    # absl_bad_optional_access
    # absl_bad_variant_access
    # absl_base
    # absl_city
    # absl_civil_time
    # absl_cord
    # absl_cord_internal
    # absl_cordz_functions
    # absl_cordz_handle
    # absl_cordz_info
    # absl_cordz_sample_token
    # absl_crc32c
    # absl_crc_cord_state
    # absl_crc_cpu_detect
    # absl_crc_internal
    # absl_debugging_internal
    # absl_demangle_internal
    # absl_die_if_null
    # absl_examine_stack
    # absl_exponential_biased
    # absl_failure_signal_handler
    # absl_flags
    # absl_flags_commandlineflag
    # absl_flags_commandlineflag_internal
    # absl_flags_config
    # absl_flags_internal
    # absl_flags_marshalling
    # absl_flags_parse
    # absl_flags_private_handle_accessor
    # absl_flags_program_name
    # absl_flags_reflection
    # absl_flags_usage
    # absl_flags_usage_internal
    # absl_graphcycles_internal
    # absl_hash
    # absl_hashtablez_sampler
    # absl_int128
    # absl_leak_check
    # absl_log_entry
    # absl_log_flags
    # absl_log_globals
    # absl_log_initialize
    # absl_log_internal_check_op
    # absl_log_internal_conditions
    # absl_log_internal_format
    # absl_log_internal_globals
    # absl_log_internal_log_sink_set
    # absl_log_internal_message
    # absl_log_internal_nullguard
    # absl_log_internal_proto
    # absl_log_severity
    # absl_log_sink
    # absl_low_level_hash
    # absl_malloc_internal
    # absl_periodic_sampler
    # absl_random_distributions
    # absl_random_internal_distribution_test_util
    # absl_random_internal_platform
    # absl_random_internal_pool_urbg
    # absl_random_internal_randen
    # absl_random_internal_randen_hwaes
    # absl_random_internal_randen_hwaes_impl
    # absl_random_internal_randen_slow
    # absl_random_internal_seed_material
    # absl_random_seed_gen_exception
    # absl_random_seed_sequences
    # absl_raw_hash_set
    # absl_raw_logging_internal
    # absl_scoped_mock_log
    # absl_scoped_set_env
    # absl_spinlock_wait
    # absl_stacktrace
    # absl_status
    # absl_statusor
    # absl_str_format_internal
    # absl_strerror
    # absl_strings
    # absl_strings_internal
    # absl_symbolize
    # absl_synchronization
    # absl_throw_delegate
    # absl_time
    # absl_time_zone

    # absl::bad_any_cast_impl
    # absl::bad_optional_access
    # absl::bad_variant_access
    # absl::base
    # absl::city
    # absl::civil_time
    # absl::cord
    # absl::cord_internal
    # absl::cordz_functions
    # absl::cordz_handle
    # absl::cordz_info
    # absl::cordz_sample_token
    # absl::crc32c
    # absl::crc_cord_state
    # absl::crc_cpu_detect
    # absl::crc_internal
    # absl::debugging_internal
    # absl::demangle_internal
    # absl::die_if_null
    # absl::examine_stack
    # absl::exponential_biased
    # absl::failure_signal_handler
    # absl::flags
    # absl::flags_commandlineflag
    # absl::flags_commandlineflag_internal
    # absl::flags_config
    # absl::flags_internal
    # absl::flags_marshalling
    # absl::flags_parse
    # absl::flags_private_handle_accessor
    # absl::flags_program_name
    # absl::flags_reflection
    # absl::flags_usage
    # absl::flags_usage_internal
    # absl::graphcycles_internal
    # absl::hash
    # absl::hashtablez_sampler
    # absl::int128
    # absl::leak_check
    # absl::log_entry
    # absl::log_flags
    # absl::log_globals
    # absl::log_initialize
    # absl::log_internal_check_op
    # absl::log_internal_conditions
    # absl::log_internal_format
    # absl::log_internal_globals
    # absl::log_internal_log_sink_set
    # absl::log_internal_message
    # absl::log_internal_nullguard
    # absl::log_internal_proto
    # absl::log_severity
    # absl::log_sink
    # absl::low_level_hash
    # absl::malloc_internal
    # absl::periodic_sampler
    # absl::random_distributions
    # absl::random_internal_distribution_test_util
    # absl::random_internal_platform
    # absl::random_internal_pool_urbg
    # absl::random_internal_randen
    # absl::random_internal_randen_hwaes
    # absl::random_internal_randen_hwaes_impl
    # absl::random_internal_randen_slow
    # absl::random_internal_seed_material
    # absl::random_seed_gen_exception
    # absl::random_seed_sequences
    # absl::raw_hash_set
    # absl::raw_logging_internal
    # absl::scoped_mock_log
    # absl::scoped_set_env
    # absl::spinlock_wait
    # absl::stacktrace
    # absl::status
    # absl::statusor
    # absl::str_format_internal
    # absl::strerror
    # absl::strings
    # absl::strings_internal
    # absl::symbolize
    # absl::synchronization
    # absl::throw_delegate
    # absl::time
    # absl::time_zone
)


# /usr/local/lib/libabsl_bad_any_cast_impl.a               
# /usr/local/lib/libabsl_bad_optional_access.a             
# /usr/local/lib/libabsl_bad_variant_access.a              
# /usr/local/lib/libabsl_base.a                            
# /usr/local/lib/libabsl_city.a                            
# /usr/local/lib/libabsl_civil_time.a                      
# /usr/local/lib/libabsl_cord.a                            
# /usr/local/lib/libabsl_cord_internal.a                   
# /usr/local/lib/libabsl_cordz_functions.a                 
# /usr/local/lib/libabsl_cordz_handle.a                    
# /usr/local/lib/libabsl_cordz_info.a                      
# /usr/local/lib/libabsl_cordz_sample_token.a              
# /usr/local/lib/libabsl_crc32c.a                          
# /usr/local/lib/libabsl_crc_cord_state.a                  
# /usr/local/lib/libabsl_crc_cpu_detect.a                  
# /usr/local/lib/libabsl_crc_internal.a                    
# /usr/local/lib/libabsl_debugging_internal.a              
# /usr/local/lib/libabsl_demangle_internal.a               
# /usr/local/lib/libabsl_die_if_null.a                     
# /usr/local/lib/libabsl_examine_stack.a                   
# /usr/local/lib/libabsl_exponential_biased.a              
# /usr/local/lib/libabsl_failure_signal_handler.a          
# /usr/local/lib/libabsl_flags.a                           
# /usr/local/lib/libabsl_flags_commandlineflag.a           
# /usr/local/lib/libabsl_flags_commandlineflag_internal.a  
# /usr/local/lib/libabsl_flags_config.a                    
# /usr/local/lib/libabsl_flags_internal.a                  
# /usr/local/lib/libabsl_flags_marshalling.a               
# /usr/local/lib/libabsl_flags_parse.a                    
# /usr/local/lib/libabsl_flags_private_handle_accessor.a  
# /usr/local/lib/libabsl_flags_program_name.a             
# /usr/local/lib/libabsl_flags_reflection.a               
# /usr/local/lib/libabsl_flags_usage.a                    
# /usr/local/lib/libabsl_flags_usage_internal.a           
# /usr/local/lib/libabsl_graphcycles_internal.a           
# /usr/local/lib/libabsl_hash.a                           
# /usr/local/lib/libabsl_hashtablez_sampler.a             
# /usr/local/lib/libabsl_int128.a                         
# /usr/local/lib/libabsl_leak_check.a                     
# /usr/local/lib/libabsl_log_entry.a                      
# /usr/local/lib/libabsl_log_flags.a                      
# /usr/local/lib/libabsl_log_globals.a                    
# /usr/local/lib/libabsl_log_initialize.a                 
# /usr/local/lib/libabsl_log_internal_check_op.a          
# /usr/local/lib/libabsl_log_internal_conditions.a        
# /usr/local/lib/libabsl_log_internal_format.a            
# /usr/local/lib/libabsl_log_internal_globals.a           
# /usr/local/lib/libabsl_log_internal_log_sink_set.a      
# /usr/local/lib/libabsl_log_internal_message.a           
# /usr/local/lib/libabsl_log_internal_nullguard.a         
# /usr/local/lib/libabsl_log_internal_proto.a             
# /usr/local/lib/libabsl_log_severity.a                   
# /usr/local/lib/libabsl_log_sink.a                       
# /usr/local/lib/libabsl_low_level_hash.a                 
# /usr/local/lib/libabsl_malloc_internal.a                
# /usr/local/lib/libabsl_periodic_sampler.a      
# /usr/local/lib/libabsl_random_distributions.a
# /usr/local/lib/libabsl_random_internal_distribution_test_util.a
# /usr/local/lib/libabsl_random_internal_platform.a
# /usr/local/lib/libabsl_random_internal_pool_urbg.a
# /usr/local/lib/libabsl_random_internal_randen.a
# /usr/local/lib/libabsl_random_internal_randen_hwaes.a
# /usr/local/lib/libabsl_random_internal_randen_hwaes_impl.a
# /usr/local/lib/libabsl_random_internal_randen_slow.a
# /usr/local/lib/libabsl_random_internal_seed_material.a
# /usr/local/lib/libabsl_random_seed_gen_exception.a
# /usr/local/lib/libabsl_random_seed_sequences.a
# /usr/local/lib/libabsl_raw_hash_set.a
# /usr/local/lib/libabsl_raw_logging_internal.a
# /usr/local/lib/libabsl_scoped_mock_log.a
# /usr/local/lib/libabsl_scoped_set_env.a
# /usr/local/lib/libabsl_spinlock_wait.a
# /usr/local/lib/libabsl_stacktrace.a
# /usr/local/lib/libabsl_status.a
# /usr/local/lib/libabsl_statusor.a
# /usr/local/lib/libabsl_str_format_internal.a
# /usr/local/lib/libabsl_strerror.a
# /usr/local/lib/libabsl_strings.a
# /usr/local/lib/libabsl_strings_internal.a
# /usr/local/lib/libabsl_symbolize.a
# /usr/local/lib/libabsl_synchronization.a
# /usr/local/lib/libabsl_throw_delegate.a
# /usr/local/lib/libabsl_time.a
# /usr/local/lib/libabsl_time_zone.a         

# -labsl_bad_any_cast_impl -labsl_bad_optional_access -labsl_bad_variant_access -labsl_base -labsl_city -labsl_civil_time -labsl_cord -labsl_cord_internal -labsl_cordz_functions -labsl_cordz_handle -labsl_cordz_info -labsl_cordz_sample_token -labsl_crc32c -labsl_crc_cord_state -labsl_crc_cpu_detect -labsl_crc_internal -labsl_debugging_internal -labsl_demangle_internal
# -labsl_die_if_null -labsl_examine_stack -labsl_exponential_biased -labsl_failure_signal_handler -labsl_flags -labsl_flags_commandlineflag -labsl_flags_commandlineflag_internal
# -labsl_flags_config -labsl_flags_internal -labsl_flags_marshalling -labsl_flags_parse -labsl_flags_private_handle_accessor -labsl_flags_program_name -labsl_flags_reflection
# -labsl_flags_usage -labsl_flags_usage_internal -labsl_graphcycles_internal -labsl_hash -labsl_hashtablez_sampler -labsl_int128 -labsl_leak_check -labsl_log_entry -labsl_log_flags
# -labsl_log_globals -labsl_log_initialize -labsl_log_internal_check_op -labsl_log_internal_conditions -labsl_log_internal_format -labsl_log_internal_globals -labsl_log_internal_log_sink_set -labsl_log_internal_message
# -labsl_log_internal_nullguard
# -labsl_log_internal_proto
# -labsl_log_severity
# -labsl_log_sink
# -labsl_low_level_hash
# -labsl_malloc_internal
# -labsl_periodic_sampler
# -labsl_random_distributions
# -labsl_random_internal_distribution_test_util
# -labsl_random_internal_platform
# -labsl_random_internal_pool_urbg
# -labsl_random_internal_randen
# -labsl_random_internal_randen_hwaes
# -labsl_random_internal_randen_hwaes_impl
# -labsl_random_internal_randen_slow
# -labsl_random_internal_seed_material
# -labsl_random_seed_gen_exception
# -labsl_random_seed_sequences
# -labsl_raw_hash_set
# -labsl_raw_logging_internal
# -labsl_scoped_mock_log
# -labsl_scoped_set_env
# -labsl_spinlock_wait
# -labsl_stacktrace
# -labsl_status
# -labsl_statusor
# -labsl_str_format_internal
# -labsl_strerror
# -labsl_strings
# -labsl_strings_internal
# -labsl_symbolize
# -labsl_synchronization
# -labsl_throw_delegate
# -labsl_time
# -labsl_time_zone