#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tree.h"
#include "tree-pass.h"
#include "context.h"
#include "function.h"
#include "basic-block.h"
#include "cfg.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "gimple-pretty-print.h"

namespace {
    const pass_data pass_data_ctyler = {
        GIMPLE_PASS,     
        "ctyler",         
        OPTGROUP_NONE,     
        TV_NONE,          
        PROP_cfg,          
        0,                
        0,                 
        0,                
        0                  
    };

    class pass_ctyler : public gimple_opt_pass {
    public:
        pass_ctyler(gcc::context *ctxt) : gimple_opt_pass(pass_data_ctyler, ctxt) {}

        bool gate(function *) override { return true; }

        unsigned int execute(function *fun) override {
            if (dump_file) {
                fprintf(dump_file, "Analyzing function: %s\n", IDENTIFIER_POINTER(DECL_NAME(fun->decl)));
            }

           
            basic_block bb;
            FOR_EACH_BB_FN(bb, fun) {
                gimple_stmt_iterator gsi = gsi_start_bb(bb);
                while (!gsi_end_p(gsi)) {
                    gsi_remove(&gsi, true); // Remove statement
                }
            }

            if (dump_file) {
                fprintf(dump_file, "PRUNED function: %s\n", IDENTIFIER_POINTER(DECL_NAME(fun->decl)));
            }

            return 0;
        }
    };
} // End anonymous namespace

// Factory function to create the pass
gimple_opt_pass *make_pass_ctyler(gcc::context *ctxt) {
    return new pass_ctyler(ctxt);
}
