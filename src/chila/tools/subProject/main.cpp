/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include <chila/lib/git/util.hpp>
#include <chila/lib/git/exceptions.hpp>
#include <iostream>

void showException(const std::exception &ex);

namespace clg = chila::lib::git;

int file_cb(const git_diff_delta *delta, float progress, void *payload)
{
    std::cout << delta->old_file.path << std::endl;
    std::cout << delta->new_file.path << "\n" << std::endl;
    return 0;
}

int hunk_cb(const git_diff_delta *delta, const git_diff_hunk *hunk, void *payload)
{
    std::cout << hunk->header << "\n" << std::endl;

    return 0;
}

int line_cb(const git_diff_delta *delta, const git_diff_hunk *hunk, const git_diff_line *line, void *payload)
{
//    std::cout << line-> << "\n" << std::endl;
    return 0;
}

int main(int argc, char **argv) try
{
    git_blob *blob = nullptr;
    git_repository *repo = nullptr;

    clg::check(git_repository_open(&repo, "."), "error opening file");

    git_object *obj = NULL;
    clg::check(git_revparse_single(&obj, repo, "53e01f67e006094eaa09ecd346defd29f8cdb8c9"));

    git_commit *commit = NULL;
    clg::check(git_commit_lookup(&commit, repo, git_object_id(obj)));

    git_commit *parent = NULL;
    clg::check(git_commit_parent(&parent, commit, 0));

    git_tree *commit_tree = NULL, *parent_tree = NULL;
    clg::check(git_commit_tree(&commit_tree, commit));
    clg::check(git_commit_tree(&parent_tree, parent));

    git_diff *diff = NULL;
    clg::check(git_diff_tree_to_tree(&diff, repo, commit_tree, parent_tree, NULL));

    clg::check(git_diff_foreach(diff, file_cb, hunk_cb, line_cb, nullptr));

    

    return EXIT_SUCCESS;
}
catch (const chila::lib::git::Exception &ex)
{
    showException(ex);
    return EXIT_FAILURE;
}
//catch (const clXmlPPUtils::Exception &ex)
//{
//    showException(ex);
//    return EXIT_FAILURE;
//}

#define show_error_info(out, Type, name) \
        if (const Type::error_info::value_type *value = boost::get_error_info<Type>(ex)) \
            out << "- " << name << ": " << "[" << *value << "]" << std::endl;

void showException(const std::exception &ex)
{
    std::cerr << ex.what() << std::endl;

//    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Path, "path");
//    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::XPath, "xml path");
//    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Row, "row");
//    show_error_info(std::cerr, chila::lib::misc::ExceptionInfo::Column, "column");
}
