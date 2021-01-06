echo "<<< NEXT SHOULD BE VALID >>>"
echo " "
echo "*Valid 1:"
./lem-in < maps/subject.map
echo " "
echo "*Valid Map2-2:"
./lem-in < maps/subject2-2.map
echo " "
echo "*Valid 2-1:"
./lem-in < maps/subject2-1.map
echo " "
echo "*Valid 3:"
./lem-in < maps/subject3.map
echo " "
echo "*Valid A3:"
./lem-in < maps/a_subject3.map
echo " "
echo "*Map with comments extra:"
./lem-in < maps/v_extra.map
echo " "
echo "*Map with comments and extra commands:"
./lem-in < maps/v_with_cmds_and_cmnts.map
echo " "
echo "*Map with comments:"
./lem-in < maps/v_with_comments.map
echo " "
echo "*Valid: Subject example map:"
./lem-in < maps/v_subject_example.map
echo " "
# echo "*Valid: Anamy's map with 1 ant:"
# ./lem-in < maps/v_anamy1.map
# echo " "
echo "*Valid: Anamy's that-map:"
./lem-in < maps/v_anamy_that.map
echo " "
# echo "*Valid: Test map:" #says invalid because of spaces in room name
# ./lem-in < maps/v_test_map.map
# echo " "
# echo "*Valid: Anamy's map with 15 ants:" // the next ones below give routing error
# ./lem-in < maps/v_anamy10.map
# echo " "
# echo "*Valid: Anamy's map with 120 ants:"
# ./lem-in < maps/v_anamy1000.map
# echo " "
# echo "*Valid: Anamy's huge map:"
# ./lem-in < maps/v_huge_map.map
# echo " "

echo "<<< PONDERING >>>"
echo " "

echo "?. Link to itself:" #should not print the contents of farm?
./lem-in < maps/p_link_to_itself.map
echo " "
echo "*Valid: Lots of rooms and links map:"
./lem-in < maps/v_lots.map
echo " "

#v_lots: all ants are using one route from start to end; figured out we must allow only one ant for one route per turn.
