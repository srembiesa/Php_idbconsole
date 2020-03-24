<?php
# * ********************************************************************* *
# *                                                                       *
# *   PHP IDB console tools                                               *
# *   This file is part of idbconsole. This project may be found at:      *
# *   https://github.com/IdentityBank/Php_idbconsole.                     *
# *                                                                       *
# *   Copyright (C) 2020 by Identity Bank. All Rights Reserved.           *
# *   https://www.identitybank.eu - You belong to you                     *
# *                                                                       *
# *   This program is free software: you can redistribute it and/or       *
# *   modify it under the terms of the GNU Affero General Public          *
# *   License as published by the Free Software Foundation, either        *
# *   version 3 of the License, or (at your option) any later version.    *
# *                                                                       *
# *   This program is distributed in the hope that it will be useful,     *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of      *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        *
# *   GNU Affero General Public License for more details.                 *
# *                                                                       *
# *   You should have received a copy of the GNU Affero General Public    *
# *   License along with this program. If not, see                        *
# *   https://www.gnu.org/licenses/.                                      *
# *                                                                       *
# * ********************************************************************* *

################################################################################
# Use(s)                                                                       #
################################################################################

use idbyii2\models\db\BusinessDatabaseData;
use idbyii2\models\idb\IdbBankClientBusiness;

################################################################################
# Migration                                                                    #
################################################################################

$dbModels = BusinessDatabaseData::find()->all();

foreach ($dbModels as $model) {
    try{
        $businessId = $model->business_db_id;

        $clientModel = IdbBankClientBusiness::model($businessId);
        $metadata = json_decode($clientModel->getAccountMetadata()['Metadata'], true);
        unset($metadata['headerMapping']);
        $clientModel->setAccountMetadata(json_encode($metadata));

    }  catch (Exception $e) {
        $this->migrationError($e->getMessage());

        return ExitCode::UNSPECIFIED_ERROR;
    }
}


################################################################################
#                                End of file                                   #
################################################################################