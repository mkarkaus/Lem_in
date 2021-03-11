echo "<<< NEXT SHOULD BE VALID >>>"
echo " "

echo "*Valid 1:"
./lem-in -rl < maps/subject.map
echo " "

echo "*Valid Map2-2:"
./lem-in -rl < maps/subject2-2.map
echo " "

echo "*Valid 2-1:"
./lem-in -rl < maps/subject2-1.map
echo " "

echo "*Valid 3:"
./lem-in -rl < maps/subject3.map
echo " "

echo "*Valid A3:"
./lem-in -rl < maps/a_subject3.map
echo " "

echo "*Map with comments extra:"
./lem-in -rl < maps/v_extra.map
echo " "

echo "*Map with comments and extra commands:"
./lem-in -rl < maps/v_with_cmds_and_cmnts.map
echo " "

echo "*Map with comments:"
./lem-in -rl < maps/v_with_comments.map
echo " "

echo "*Valid: Subject example map:"
./lem-in -rl < maps/v_subject_example.map
echo " "

echo "*Valid: Loop:"
./lem-in -rl < maps/v_loop.map
echo " "

echo "*Valid: dead:"
./lem-in -rl < maps/v_dead.map
echo " "

echo "*Valid: deadend:"
./lem-in -rl < maps/v_deadend.map
echo " "

echo "*Valid: deadend2:"
./lem-in -rl < maps/v_deadend2.map
echo " "

echo "*Valid: Anamy's that-map:"
./lem-in -rl < maps/v_anamy_that.map
echo " "

echo "*Valid: Lots of links per room map:"
./lem-in -rl < maps/v_lots.map
echo " "

echo "?. Valid: Link to itself:"
./lem-in -rl < maps/v_link_to_itself.map
echo " "

echo "?. Giving same coors to two separate rooms:"
./lem-in -rl < maps/v_giving_same_coor.map
echo " "

echo "?. Superconnected map:"
./lem-in -rl < maps/v_superconnection.map
echo " "

# echo "?. MAX_INT ants:"
# ./lem-in -rl < maps/v_max_ants.map
echo " "

# echo "*Valid: Test map:" #says invalid because of spaces in room name
# ./lem-in -rl < maps/v_test_map.map
# echo " "

# echo "?. Valid: Lots of links with duplicate links between rooms:"
# ./lem-in -rl -q < maps/v_dup_links.map
# echo " "

# echo "*Valid: Anamy's huge map:"
# ./lem-in -rl -q < maps/v_huge_map.map
# echo " "
