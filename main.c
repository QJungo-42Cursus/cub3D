#include "libft/libft.h"
#include "cube3D.h"

static int	is_arg_name_valid(int argc, char **argv)
{
	int		len;

	if (argc != 2)
		return (FALSE);
	len = ft_strlen(argv[1]);
	if (len < 5)
		return (FALSE);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 5) != 0)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	if (!is_arg_name_valid(argc, argv))
	{
		ft_printf("error\n", argv[0]);
		return (1);
	}
	parse(argv[1]);
	return (0);
}
