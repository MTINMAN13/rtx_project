
#include "miniRT.h"

//If it finds a C, it will ram the data into scene->viewport
//If it finds other shit, it will do it into scene->objects->raw_data
//It then tells us how many objects are there

int	ft_parse(int fd, t_scene **scene)
{
	ft_pntf("beep boop im a parser\n %s", get_next_line(fd));
	ft_pntf("suppressor %i", scene);
	return(EXIT_SUCCESS);
}
