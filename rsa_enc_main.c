#include <unistd.h>
#include <getopt.h>
#include "rsa_util.h"
#include "rsa_enc.h"
#include "rsa.h"

static opt_t options_encrypter[] = {
    {RSA_OPT_FILE, 'f', "file", required_argument, "input file to encrypt"},
    {RSA_OPT_LEVEL, 'l', "level", required_argument, "set encryption level to "
	"128, 256, 512 or 1024 (default)"},
    {RSA_OPT_RSAENC, 'r', "rsa", no_argument, "full RSA encryption. if this "
	"flag is not set, encryption will be done using a symmetric "
	"key and only it will be RSA encrypted"},
    { RSA_OPT_MAX }
};

/* encryption task is to be performed */
static int parse_args_finalize_encrypter(int *flags, int actions)
{
    if (!actions)
	*flags |= OPT_FLAG(RSA_OPT_ENCRYPT);

    /* test for non compatable options with encrypt */
    if ((*flags & OPT_FLAG(RSA_OPT_ENCRYPT)) && 
	!(*flags & OPT_FLAG(RSA_OPT_FILE)))
    {
	rsa_error_message(RSA_ERR_NOFILE);
	return -1;
    }

    return 0;
}

static int parse_args_encrypter(int opt, int *flags)
{
    switch (opt_short2code(options_encrypter, opt))
    {
    case RSA_OPT_FILE:
	OPT_ADD(flags, RSA_OPT_FILE);
	if (rsa_set_file_name(optarg))
	{
	    rsa_error_message(RSA_ERR_FNAME_LEN, optarg);
	    return -1;
	}
	break;
    case RSA_OPT_LEVEL:
	OPT_ADD(flags, RSA_OPT_LEVEL);
	if (rsa_encryption_level_set(optarg))
	{
	    rsa_error_message(RSA_ERR_LEVEL, optarg);
	    return -1;
	}
	break;
    case RSA_OPT_RSAENC:
	OPT_ADD(flags, RSA_OPT_RSAENC);
	break;
    default:
	rsa_error_message(RSA_ERR_OPTARG);
	return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int action, flags = 0;
    rsa_handler_t encrypter_handler = {
	.keytype = RSA_KEY_TYPE_PUBLIC,
	.options = options_encrypter,
	.ops_handler = parse_args_encrypter,
	.ops_handler_finalize = parse_args_finalize_encrypter,
    };

    if (parse_args(argc, argv, &flags, &encrypter_handler))
	return rsa_error(argv[0]);

    action = rsa_action_get(flags, RSA_OPT_ENCRYPT, NULL);
    switch (action)
    {
    case OPT_FLAG(RSA_OPT_ENCRYPT):
    {
	if (flags & OPT_FLAG(RSA_OPT_LEVEL))
	    RSA_TBD("handle RSA_OPT_LEVEL");
	if (flags & OPT_FLAG(RSA_OPT_RSAENC))
	    RSA_TBD("handle RSA_OPT_RSAENC");

	RSA_TBD("handle RSA_OPT_ENCRYPT");
	break;
    }
    default:
	return rsa_action_handle_common(action, argv[0], &encrypter_handler);
    }

    return 0;
}
