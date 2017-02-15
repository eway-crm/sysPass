<?php
/**
 * sysPass
 *
 * @author    nuxsmin
 * @link      http://syspass.org
 * @copyright 2012-2017, Rubén Domínguez nuxsmin@$syspass.org
 *
 * This file is part of sysPass.
 *
 * sysPass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sysPass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with sysPass.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace SP\Core\Upgrade;

use SP\Storage\DB;
use SP\Storage\QueryData;

/**
 * Class Check
 * @package SP\Core\Upgrade
 */
class Check
{
    public static function checkConstraints()
    {
        $query = /** @lang SQL */
            'SELECT * FROM 
            (SELECT COUNT(*) AS accounts_user FROM accounts WHERE account_userId NOT IN (SELECT user_id FROM usrData)) a,
            (SELECT COUNT(*) AS accounts_useredit FROM accounts WHERE account_userEditId NOT IN (SELECT user_id FROM usrData)) b,
            (SELECT COUNT(*) AS accounts_category FROM accounts WHERE account_categoryId NOT IN (SELECT category_id FROM categories)) c,
            (SELECT COUNT(*) AS accounts_customer FROM accounts WHERE account_customerId NOT IN (SELECT customer_id FROM customers)) d,
            (SELECT COUNT(*) AS accountshistory_user FROM accHistory WHERE acchistory_userId NOT IN (SELECT user_id FROM usrData)) e,
            (SELECT COUNT(*) AS accountshistory_useredit FROM accHistory WHERE acchistory_userEditId NOT IN (SELECT user_id FROM usrData)) f,
            (SELECT COUNT(*) AS accountshistory_category FROM accHistory WHERE acchistory_categoryId NOT IN (SELECT category_id FROM categories)) g,
            (SELECT COUNT(*) AS accountshistory_customer FROM accHistory WHERE acchistory_customerId NOT IN (SELECT customer_id FROM customers)) h,
            (SELECT COUNT(*) AS users_group FROM usrData WHERE user_groupId NOT IN (SELECT usergroup_id FROM usrGroups)) i,
            (SELECT COUNT(*) AS users_profile FROM usrData WHERE user_profileId NOT IN (SELECT userprofile_id FROM usrProfiles)) j';

        $Data = new QueryData();
        $Data->setQuery($query);

        return DB::getResults($Data);
    }
}