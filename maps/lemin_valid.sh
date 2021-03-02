echo "<<< NEXT SHOULD BE VALID >>>"
echo " "
echo "*Valid 1:"
valgrind --leak-check=full ./lem-in < maps/subject.map
echo " "
echo "*Valid Map2-2:"
valgrind --leak-check=full ./lem-in < maps/subject2-2.map
echo " "
echo "*Valid 2-1:"
valgrind --leak-check=full ./lem-in < maps/subject2-1.map
echo " "
echo "*Valid 3:"
valgrind --leak-check=full ./lem-in < maps/subject3.map
echo " "
echo "*Valid A3:"
valgrind --leak-check=full ./lem-in < maps/a_subject3.map
echo " "
echo "*Map with comments extra:"
valgrind --leak-check=full ./lem-in < maps/v_extra.map
echo " "
echo "*Map with comments and extra commands:"
valgrind --leak-check=full ./lem-in < maps/v_with_cmds_and_cmnts.map
echo " "
echo "*Map with comments:"
valgrind --leak-check=full ./lem-in < maps/v_with_comments.map
echo " "
echo "*Valid: Subject example map:"
valgrind --leak-check=full ./lem-in < maps/v_subject_example.map
echo " "
echo "*Valid: Loop:"
valgrind --leak-check=full ./lem-in < maps/v_loop.map
echo " "
echo "*Valid: dead:"
valgrind --leak-check=full ./lem-in < maps/v_dead.map
echo " "
echo "*Valid: deadend:"
valgrind --leak-check=full ./lem-in < maps/v_deadend.map
echo " "
echo "*Valid: deadend2:"
valgrind --leak-check=full ./lem-in < maps/v_deadend2.map
echo " "
echo "*Valid: Anamy's that-map:"
valgrind --leak-check=full ./lem-in < maps/v_anamy_that.map
echo " "
# echo "*Valid: Test map:" #says invalid because of spaces in room name
# ./lem-in < maps/v_test_map.map
# echo " "
echo "*Valid: Lots of links per room map:"
valgrind --leak-check=full ./lem-in < maps/v_lots.map
echo " "
echo "?. Valid: Link to itself:"
valgrind --leak-check=full ./lem-in < maps/v_link_to_itself.map
echo " "
# echo "?. Valid: Lots of links with duplicate links between rooms:"
# ./lem-in -q < maps/v_dup_links.map
# echo " "
# echo "*Valid: Anamy's map with 1 ant:"
# ./lem-in -q < maps/v_anamy1.map
# echo " "
# echo "*Valid: Anamy's map with 15 ants:" // the next ones below give routing error
# ./lem-in -q < maps/v_anamy10.map
# echo " "
# echo "*Valid: Anamy's map with 120 ants:"
# ./lem-in -q < maps/v_anamy1000.map
# echo " "
# echo "*Valid: Anamy's huge map:"
# ./lem-in -q < maps/v_huge_map.map
# echo " "