#include <CSVGI.h>

CSVGDesc::
CSVGDesc(CSVG &svg) :
 CSVGObject(svg), text_()
{
}

CSVGDesc::
CSVGDesc(const CSVGDesc &desc) :
 CSVGObject(desc),
 text_     (desc.text_)
{
}

CSVGDesc *
CSVGDesc::
dup() const
{
  return new CSVGDesc(*this);
}

/* Attributes:
    <Core>
    <Style>
*/
bool
CSVGDesc::
processOption(const string &opt_name, const string &opt_value)
{
  return CSVGObject::processOption(opt_name, opt_value);
}

void
CSVGDesc::
draw()
{
}

void
CSVGDesc::
print(ostream &os) const
{
  os << "desc";
}

ostream &
operator<<(ostream &os, const CSVGDesc &desc)
{
  desc.print(os);

  return os;
}
