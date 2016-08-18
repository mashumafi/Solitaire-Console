#include <Archive.hpp>

#if !defined( WIN32 )
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE archive_test_module
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ArchiveSuite)

BOOST_AUTO_TEST_CASE(get_root_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  BOOST_CHECK(root->name() == "root");
  BOOST_CHECK(root->make("child")->name() == "child");
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(get_root_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  BOOST_CHECK(root->name() == "root");
  DirectoryStream* child = root->getAbsDir(0);
  BOOST_CHECK(child->name() == "child");
  iarchive.close();
}

BOOST_AUTO_TEST_SUITE_END()
