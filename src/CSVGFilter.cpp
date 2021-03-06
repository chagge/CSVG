#include <CSVGI.h>

CSVGFilter::
CSVGFilter(CSVG &svg) :
 CSVGObject(svg),
 object_   (NULL)
{
}

CSVGFilter::
CSVGFilter(const CSVGFilter &filter) :
 CSVGObject(filter),
 object_   (NULL)
{
}

CSVGFilter *
CSVGFilter::
dup() const
{
  return new CSVGFilter(*this);
}

bool
CSVGFilter::
processOption(const string &opt_name, const string &opt_value)
{
  string str;

  if      (svg_.stringOption(opt_name, opt_value, "filterUnits", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "primitiveUnits", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "x", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "y", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "width", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "height", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "filterRes", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "color-interpolation-filters", str))
    ;
  else if (svg_.stringOption(opt_name, opt_value, "xlink:href", str))
    ;
  else
    return CSVGObject::processOption(opt_name, opt_value);

  return true;
}

void
CSVGFilter::
draw()
{
}

CImagePtr
CSVGFilter::
filterImage(CImagePtr image)
{
  svg_.setBufferImage("SourceGraphic", image);

  ObjectList::const_iterator p1, p2;

  for (p1 = childrenBegin(), p2 = childrenEnd(); p1 != p2; ++p1) {
    CSVGFilter *filter = dynamic_cast<CSVGFilter *>(*p1);

    if (filter)
      filter->draw();
  }

  image = svg_.getBufferImage("SourceGraphic");

  return image;
}

void
CSVGFilter::
print(ostream &os) const
{
  os << "filter ";
}

ostream &
operator<<(ostream &os, const CSVGFilter &filter)
{
  filter.print(os);

  return os;
}
