#ifndef serialization_HPP
# define serialization_HPP

# include <iostream>
# include <string>

uintptr_t serialize(Data * ptr);
Data * deserialize(uintptr_t raw);

#endif
