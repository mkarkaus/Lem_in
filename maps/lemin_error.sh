
echo "<<< NEXT SHOULD BE ERRORS >>>"
echo " "
echo "*1. No ants:"
./lem-in < maps/e_no_ants.map
echo " "
echo "2. Zero ants:"
./lem-in < maps/e_zero_ants.map
echo " "
echo "3. Command after start:"
./lem-in < maps/e_cmd_after_start.map
echo " "
echo "4. Command after end:"
./lem-in < maps/e_cmd_after_end.map
echo " "
echo "5. Comment after end:"
./lem-in < maps/e_cmmnt_after_end.map
echo " "
echo "6. No start room:"
./lem-in < maps/e_no_startrm.map
echo " "
echo "7. No end room:"
./lem-in < maps/e_no_endrm.map
echo " "
echo "8. No route to end:"
./lem-in < maps/e_no_route_end.map
echo " "
echo "9. No route from start:"
./lem-in < maps/e_no_route_start.map
echo " "
echo "10. Double end:" #should not print the contents of farm?
./lem-in < maps/e_double_end.map
echo " "
echo "*11. Empty map:"
./lem-in < maps/e_empty.map
echo " "
echo "*12. Non-existant map:"
./lem-in < maps/murmeli.map
echo " "

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
echo "*Map with comments:"
./lem-in < maps/v_extra.map
echo " "
echo "*Map with comments and extra commands:"
./lem-in < maps/v_with_cmds_and_cmnts.map
echo " "
echo "*Map with comments:"
./lem-in < maps/v_with_comments.map

echo "<<< PONDERING >>>"
echo " "
echo "?. Giving same coors to two separate rooms:" #should not print the contents of farm?
./lem-in < maps/p_giving_same_coor.map
echo " "
echo "?. Same name, different co-ors:" #should not print the contents of farm?
./lem-in < maps/p_giving_same_coor.map
echo " "
echo "?. Listing the same room and co-ors twice:" #should not print the contents of farm?
./lem-in < maps/p_listing_same_rm_twice.map
echo " "
echo "?. Link to itself:" #should not print the contents of farm?
./lem-in < maps/p_link_to_itself.map
echo " "
echo "?. Link is left open:" #should not print the contents of farm?
./lem-in < maps/p_open_link.map
echo " "
echo "?. Link is left open b:" #should not print the contents of farm?
./lem-in < maps/p_open_link.map
echo " "
echo "?. Link is left open (no line):" #should not print the contents of farm?
./lem-in < maps/p_open_link_no_line.map
echo " "
echo "?. Start is same as end:" #should not print the contents of farm?
./lem-in < maps/p_start_is_end.map
echo " "
