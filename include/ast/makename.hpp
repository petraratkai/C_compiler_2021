#ifndef makename_hpp
#define makename_hpp

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "." + base+"_"+std::to_string(makeNameUnq++);
}

#endif
