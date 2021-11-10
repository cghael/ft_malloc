# ft_malloc
***This project is about implementing a dynamic memory allocation
mechanism***

Before embarking on this project, I thought there was some kind of magic going on in the malloc. In fact, it turned out that this is just a wrapper over system calls (in our case, mmap()) with allocated memory management functions.

## Mandatory part
* With performance in mind, you must limit the number of calls to mmap(), but also to munmap(). You have to “pre-allocate” some memory zones to store your “small” and “medium” malloc.
* Each zone must contain at least 100 allocations.
* The allowed_size of these zones must be a multiple of getpagesize().
* You also must write a function that allows visual on the state of the allocated memory
zones. 

## How can we limit the number of calls to mmap()
First of all, every our chunk of allocated memory will have a structure that describes properties.
```
typedef struct		s_chunk
{
	unsigned char	status;         // is this memory free or not
	unsigned int	allowed_size;           // the allowed_size of the allocated chunk
	struct s_chunk	*next;
}                       t_chunk;
```
Thus, we get the following structure:
```
                    C H U N K
 -----------------------------------------------
| t_chunk |  requested memory for some program  |
 -----------------------------------------------
      allowed_size = requested allowed_size + sizeof(t_chunk)
```
Then we wiil group this chunks into zones, where we can contain >= 100 allocations
```
typedef struct		s_zone
{
	t_chunk		*start;			// first allocated chunk in zone
	unsigned int	status;			// three types of zones: TINY, SMALL, LARGE
	unsigned int	free_size;		// how much free space is left in one zone
	unsigned int	allowed_size;			// total allowed_size of the zone
	struct s_zone	*next;
}			t_zone;
```
Tiny and small chunks we will be store in such zones.
Then we get the following
```
Z O N E (status == TINY || status == SMALL)
 --------------------------------------
|        |       |       |     |       |
| t_zone | CHUNK | CHUNK | ... | CHUNK |
|        |       |       |     |       |
 --------------------------------------
allowed_size = sizeof(t_zone) + sizeof(chunk) * n_chunks + free_size
```
Large chunks we will be store out of zone
```
        Z O N E (status == LARGE)
 --------------------------------------
|        |                             |
| t_zone |    L A R G E   C H U N K    |
|        |                             |
 --------------------------------------
  allowed_size = sizeof(t_zone) + sizeof(chunk)
```

Thus, we will call mmap() and ask the system for memory the allowed_size of a zone, and then, if necessary, issue new chunks from this zone for the program.

We will have one variable that will store the head of the list of allocated zones and a pointer to the current zone in which we can provide the next chunk of memory
```
typedef struct		s_info
{
	t_zone		*start;
	t_zone		*current;
}			t_info;
```
