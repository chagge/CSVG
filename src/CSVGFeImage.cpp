#include <CSVGI.h>

CSVGFeImage::
CSVGFeImage(CSVG &svg) :
 CSVGFilter (svg),
 xlink_     (this),
 filter_out_("SourceGraphic")
{
}

CSVGFeImage::
CSVGFeImage(const CSVGFeImage &image) :
 CSVGFilter (image),
 xlink_     (image.xlink_),
 filter_out_(image.filter_out_)
{
}

CSVGFeImage *
CSVGFeImage::
dup() const
{
  return new CSVGFeImage(*this);
}

bool
CSVGFeImage::
processOption(const string &opt_name, const string &opt_value)
{
  string str;

  if      (svg_.stringOption(opt_name, opt_value, "xlink:href", str))
    xlink_ = CSVGXLink(this, str);
  else if (svg_.stringOption(opt_name, opt_value, "result", str))
    filter_out_ = str;
  else
    return CSVGFilter::processOption(opt_name, opt_value);

  return true;
}

void
CSVGFeImage::
draw()
{
  CImagePtr src_image;

  if      (xlink_.isImage())
    src_image = xlink_.getImage();
  else if (xlink_.isObject())
    src_image = xlink_.getObject()->toImage();

  CImagePtr dst_image = filterImage(src_image);

  svg_.setBufferImage(filter_out_, dst_image);
}

CImagePtr
CSVGFeImage::
filterImage(CImagePtr src_image)
{
  if (! src_image.isValid()) return CImagePtr();

  CImagePtr dst_image = src_image->dup();

  CSVGFilter *filter = NULL;

  CSVGObject *parent = parent_;

  while (parent != NULL) {
    filter = dynamic_cast<CSVGFilter *>(parent);

    if (filter != NULL) break;
  }

  if (filter) {
    CBBox2D bbox;

    filter->getObject()->getBBox(bbox);

    if (bbox.isSet())
      dst_image->reshape(bbox.getWidth(), bbox.getHeight());
  }

  return dst_image;
}

void
CSVGFeImage::
print(ostream &os) const
{
  os << "feImage ";
}

ostream &
operator<<(ostream &os, const CSVGFeImage &filter)
{
  filter.print(os);

  return os;
}
