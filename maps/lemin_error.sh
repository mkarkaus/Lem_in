
echo "<<< NEXT 9 SHOULD BE ERRORS >>>"
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
echo "11. Giving same coors to two separate rooms:" #should not print the contents of farm?
./lem-in < maps/giving_same_coor.map
echo " "
echo "11. Listing the same room and coors twice:" #should not print the contents of farm?
./lem-in < maps/listing_same_rm_twice.map
echo " "

echo "<<< NEXT 7 SHOULD BE VALID >>>"
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
echo "*Map with comments and extra commands:"
./lem-in < maps/with_cmds_and_cmnts.map #ei hyväksy
echo " "
echo "*Map with comments:"
./lem-in < maps/with_comments.map
