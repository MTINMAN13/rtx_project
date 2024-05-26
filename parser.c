
#include "miniRT.h"

// Function to parse the sphere data
void parse_sphere_data(char* line, t_scene** scene) {
	// Check if the line starts with 'sp'
	if (ft_strncmp(line, "sp", 2) == 0) {
		// Extract the sphere data from the line
		// Assuming the format is "sp x y z radius"
		float x, y, z, radius;
		sscanf(line, "sp %f %f %f %f", &x, &y, &z, &radius);
		// Create a new sphere object
		t_sphere* sphere = malloc(sizeof(t_sphere));
		sphere->center.x = x;
		sphere->center.y = y;
		sphere->center.z = z;
		sphere->radius = radius;
		// Add the sphere to the scene's object list
		(*scene)->objects->raw_data[(*scene)->objects->count] = sphere;
		(*scene)->total_objects++;
	}
}

// Function to parse the plane data
void parse_plane_data(char* line, t_scene** scene) {
	// Check if the line starts with 'pl'
	if (ft_strncmp(line, "pl", 2) == 0) {
		// Extract the plane data from the line
		// Assuming the format is "pl x y z nx ny nz"
		float x, y, z, nx, ny, nz;
		sscanf(line, "pl %f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz);
		// Create a new plane object
		t_plane* plane = malloc(sizeof(t_plane));
		plane->point.x = x;
		plane->point.y = y;
		plane->point.z = z;
		plane->normal.x = nx;
		plane->normal.y = ny;
		plane->normal.z = nz;
		// Add the plane to the scene's object list
		(*scene)->objects->raw_data[(*scene)->objects->count] = plane;
		(*scene)->total_objects++;
	}
}

// Function to parse the cylinder data
void parse_cylinder_data(char* line, t_scene** scene) {
	// Check if the line starts with 'cl'
	if (ft_strncmp(line, "cl", 2) == 0) {
		// Extract the cylinder data from the line
		// Assuming the format is "cl x y z nx ny nz diameter height"
		float x, y, z, nx, ny, nz, diameter, height;
		sscanf(line, "cl %f %f %f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz, &diameter, &height);
		// Create a new cylinder object
		t_cylinder* cylinder = malloc(sizeof(t_cylinder));
		cylinder->center.x = x;
		cylinder->center.y = y;
		cylinder->center.z = z;
		cylinder->normal.x = nx;
		cylinder->normal.y = ny;
		cylinder->normal.z = nz;
		cylinder->diameter = diameter;
		cylinder->height = height;
		// Add the cylinder to the scene's object list
		(*scene)->objects->raw_data[(*scene)->objects->count] = cylinder;
		(*scene)->objects->count++;
	}
}

void parse_camera_data(char* line, t_scene** scene)
{
	char	**split;
	t_vec	*coords;
	t_vec	*orientation;

	split = NULL;
	coords = NULL;
	orientation = NULL;
	if (ft_strncmp(line, "C", 1) == 0) 
	{	
		split = ft_split(line, ' ');
	}
}

// Function to parse the input file
//If it finds a C, it will ram the data into scene->viewport
//If it finds other shit, it will do it into scene->objects->raw_data
//It then tells us how many objects are there
int ft_parse(int fd, t_scene** scene)
{
	char	*line;

	line = NULL;
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			ft_pntf("beep boop im a parser\n %s", line);

			// Parse the line starting with 'C'
			parse_camera_data(line, scene);
			// Parse the line starting with 'sp'
			parse_sphere_data(line, scene);
			// Parse the line starting with 'pl'
			parse_plane_data(line, scene);
			// Parse the line starting with 'cl'
			parse_cylinder_data(line, scene);
			// Get the next line
			line = get_next_line(fd);
		}
	}
	return (EXIT_SUCCESS);
}