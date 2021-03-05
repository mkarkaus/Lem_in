echo "\e[0;31m"
echo "<<< NEXT SHOULD BE ERRORS >>>"
echo " \e[0;0m"
echo "1. No ants:"
valgrind --leak-check=full ./lem-in < maps/e_no_ants.map

echo " \e[0;31m"
echo "2. Zero ants:"
valgrind --leak-check=full ./lem-in < maps/e_zero_ants.map

echo " \e[0;0m"
echo "3. Command after start:"
valgrind --leak-check=full ./lem-in < maps/e_cmd_after_start.map

echo " \e[0;31m"
echo "4. Command after end:"
valgrind --leak-check=full ./lem-in < maps/e_cmd_after_end.map

echo " \e[0;0m"
echo "5. Comment after end:"
valgrind --leak-check=full ./lem-in < maps/e_cmmnt_after_end.map

echo " \e[0;31m"
echo "6. No start room:"
valgrind --leak-check=full ./lem-in < maps/e_no_startrm.map

echo " \e[0;0m"
echo "7. No end room:"
valgrind --leak-check=full ./lem-in < maps/e_no_endrm.map

echo " \e[0;31m"
echo "8. No links:"
valgrind --leak-check=full ./lem-in < maps/e_no_links.map

echo " \e[0;0m"
echo "9. No rooms:"
valgrind --leak-check=full ./lem-in < maps/e_no_rooms.map

echo " \e[0;31m"
echo "10. No route to end:"
valgrind --leak-check=full ./lem-in < maps/e_no_route_end.map

echo " \e[0;0m"
echo "11. No route from start:"
valgrind --leak-check=full ./lem-in < maps/e_no_route_start.map

echo " \e[0;31m"
echo "12. Double end:"
valgrind --leak-check=full ./lem-in < maps/e_double_end.map

echo " \e[0;0m"
echo "*11. Empty map:"
valgrind --leak-check=full ./lem-in < maps/e_empty.map

echo " \e[0;31m"
echo "*12. Non-existant map:"
valgrind --leak-check=full ./lem-in < maps/murmeli.map

echo " \e[0;0m"
echo "?. Link is left open:"
valgrind --leak-check=full ./lem-in < maps/e_open_link.map

echo " \e[0;31m"
echo "?. Link is left open b:"
valgrind --leak-check=full ./lem-in < maps/e_open_link.map

echo " \e[0;0m"
echo "?. Link is left open (no line):"
valgrind --leak-check=full ./lem-in < maps/e_open_link_no_line.map

echo " \e[0;31m"
echo "?. Invalid link to Timbuktu:"
valgrind --leak-check=full ./lem-in < maps/e_invalid_link.map

echo " \e[0;0m"
echo "?. Letter in co-ors:"
valgrind --leak-check=full ./lem-in < maps/e_letter_in_coors.map

echo " \e[0;31m"
echo "?. Too many co-ors:"
valgrind --leak-check=full ./lem-in < maps/e_too_many_coors.map

echo " \e[0;0m"
echo "?. Start is same as end:"
valgrind --leak-check=full ./lem-in < maps/e_start_is_end.map

echo " \e[0;31m"
echo "?. Same name, different co-ors:"
valgrind --leak-check=full ./lem-in < maps/e_same_room_diff_coors.map

echo " \e[0;0m"
echo "?. Listing the same room and co-ors twice:"
valgrind --leak-check=full ./lem-in < maps/e_listing_same_rm_twice.map
echo " "
