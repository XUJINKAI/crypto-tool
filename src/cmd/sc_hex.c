#include "cc/format/hex.h"
#include "cmd_helper.h"
#include "cmdparser.h"
#include "global.h"

static cmdp_action_t __process(cmdp_process_param_st *params);

static struct
{
    bool decode;
    char *instring;
    char *infile;
    char *outfile;
} __args;

cmdp_command_st sc_hex = {
    .name = "hex",
    .desc = "hex encode/decode",
    .doc  = "hex [-d] -s STRING\n",
    .options =
        (cmdp_option_st[]){
            {'d', "decode", "decode", CMDP_TYPE_BOOL, &__args.decode},
            _opt_intext(__args.instring, ),
            _opt_infile(__args.infile, ),
            _opt_outfile(__args.outfile, ),
            {0},
        },
    .fn_process = __process,
};

static cmdp_action_t __process(cmdp_process_param_st *params)
{
    CMDP_CHECK_ARG_COUNT(params, 0, 0);

    XIO *instream  = NULL;
    XIO *outstream = NULL;

    instream  = cmd_get_instream(__args.instring, __args.infile, true);
    outstream = cmd_get_outstream(__args.outfile, true);

    if (!__args.decode)
    {
        outstream = XIO_newf_hex(outstream);
    }
    LOG_DBG_XIO("in : ", instream);
    LOG_DBG_XIO("out: ", outstream);

    if (!__args.decode)
    {
        XIO_drain(instream, outstream);
    }
    else
    {
        xbytes *all = XIO_read_all(instream, 0);
        if (!all)
        {
            LOG_ERROR("read instream failed");
            goto end;
        }
        xbytes *decoded = cc_hex_decode(xbytes_buffer(all), xbytes_length(all), CC_HEX_DEC_IGNORE_NONHEX);
        if (!decoded)
        {
            xbytes_free(all);
            LOG_ERROR("decode failed");
            goto end;
        }
        XIO_write(outstream, xbytes_buffer(decoded), xbytes_length(decoded));
        xbytes_free(decoded);
    }

end:
    xio_close_safe(instream);
    xio_close_safe(outstream);
    return CMDP_ACT_OK;
}
