echo "<<< NEXT SHOULD BE VALID >>>"
echo " "

echo "\e[0;32m"
echo "*Valid 1:"
valgrind --leak-check=full ./lem-in < maps/subject.map

echo " \e[0;0m"
echo "*Valid Map2-2:"
valgrind --leak-check=full ./lem-in < maps/subject2-2.map
echo " "

echo "\e[0;32m"
echo "*Valid 2-1:"
valgrind --leak-check=full ./lem-in < maps/subject2-1.map

echo " \e[0;0m"
echo "*Valid 3:"
valgrind --leak-check=full ./lem-in < maps/subject3.map
echo " "

echo "\e[0;32m"
echo "*Valid A3:"
valgrind --leak-check=full ./lem-in < maps/a_subject3.map

echo " \e[0;0m"
echo "*Map with comments extra:"
valgrind --leak-check=full ./lem-in < maps/v_extra.map
echo " "

echo "\e[0;32m"
echo "*Map with comments and extra commands:"
valgrind --leak-check=full ./lem-in < maps/v_with_cmds_and_cmnts.map

echo " \e[0;0m"
echo "*Map with comments:"
valgrind --leak-check=full ./lem-in < maps/v_with_comments.map
echo " "

echo "\e[0;32m"
echo "*Valid: Subject example map:"
valgrind --leak-check=full ./lem-in < maps/v_subject_example.map

echo " \e[0;0m"
echo "*Valid: Loop:"
valgrind --leak-check=full ./lem-in < maps/v_loop.map
echo " "

echo "\e[0;32m"
echo "*Valid: dead:"
valgrind --leak-check=full ./lem-in < maps/v_dead.map

echo " \e[0;0m"
echo "*Valid: deadend:"
valgrind --leak-check=full ./lem-in < maps/v_deadend.map
echo " "

echo "\e[0;32m"
echo "*Valid: deadend2:"
valgrind --leak-check=full ./lem-in < maps/v_deadend2.map

echo " \e[0;0m"
echo "*Valid: Anamy's that-map:"
valgrind --leak-check=full ./lem-in < maps/v_anamy_that.map
echo " "

echo "\e[0;32m"
echo "*Valid: Lots of links per room map:"
valgrind --leak-check=full ./lem-in < maps/v_lots.map

echo " \e[0;0m"
echo "?. Valid: Link to itself:"
valgrind --leak-check=full ./lem-in < maps/v_link_to_itself.map
echo " "

echo "\e[0;32m"
echo "?. Giving same coors to two separate rooms:"
valgrind --leak-check=full ./lem-in < maps/v_giving_same_coor.map

echo "\e[0;0m"
echo "?. MAX_INT ants:"
valgrind --leak-check=full ./lem-in < maps/v_max_ants.map

echo " \e[0;0m"
# echo "*Valid: Test map:" #says invalid because of spaces in room name
# ./lem-in < maps/v_test_map.map
# echo " "

# echo "?. Valid: Lots of links with duplicate links between rooms:"
# ./lem-in -q < maps/v_dup_links.map
# echo " "

# echo "*Valid: Anamy's huge map:"
# ./lem-in -q < maps/v_huge_map.map
# echo " "