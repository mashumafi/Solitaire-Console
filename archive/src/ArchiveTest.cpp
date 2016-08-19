#include <Archive.hpp>

#ifndef WIN32
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
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(get_root_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  BOOST_CHECK(root->name() == "root");
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(add_child_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  BOOST_CHECK(root->make("child")->name() == "child");
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(add_child_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  BOOST_CHECK(root->getAbsDir(0)->name() == "child");
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(add_children_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(add_children_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(add_recursive_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(add_recursive_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(delete_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(delete_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(delete_recursive_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(delete_recursive_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(move_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(move_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(rename_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(rename_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(is_directory_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(is_directory_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  
  iarchive.close();
}

BOOST_AUTO_TEST_CASE(is_hidden_out)
{
  std::remove("test.db");
  Archive oarchive("test.db");
  DirectoryStream* root = oarchive.getRoot();
  BOOST_CHECK(root->isDirectory());
  oarchive.close();
}

BOOST_AUTO_TEST_CASE(is_hidden_in)
{
  Archive iarchive("test.db");
  DirectoryStream* root = iarchive.getRoot();
  BOOST_CHECK(root->isDirectory());
  iarchive.close();
}

BOOST_AUTO_TEST_SUITE_END()
