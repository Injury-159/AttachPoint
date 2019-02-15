
// From Texture studio | Credits to original author.
stock AttachPoint(Float:offx, Float:offy, Float:offz, Float:offrx, Float:offry, Float:offrz, Float:px, Float:py, Float:pz, Float:prx, Float:pry, Float:prz, &Float:RetX, &Float:RetY, &Float:RetZ, &Float:RetRX, &Float:RetRY, &Float:RetRZ, sync_rotation = 1)
{
    new
        Float:g_sin[3],
        Float:g_cos[3],
        Float:off_x,
        Float:off_y,
        Float:off_z;

    EDIT_FloatEulerFix(prx, pry, prz);

    off_x = offx - px; // static offset
    off_y = offy - py; // static offset
    off_z = offz - pz; // static offset

    // Calculate the new position
    EDIT_FloatConvertValue(prx, pry, prz, g_sin, g_cos);
    RetX = px + off_x * g_cos[1] * g_cos[2] - off_x * g_sin[0] * g_sin[1] * g_sin[2] - off_y * g_cos[0] * g_sin[2] + off_z * g_sin[1] * g_cos[2] + off_z * g_sin[0] * g_cos[1] * g_sin[2];
    RetY = py + off_x * g_cos[1] * g_sin[2] + off_x * g_sin[0] * g_sin[1] * g_cos[2] + off_y * g_cos[0] * g_cos[2] + off_z * g_sin[1] * g_sin[2] - off_z * g_sin[0] * g_cos[1] * g_cos[2];
    RetZ = pz - off_x * g_cos[0] * g_sin[1] + off_y * g_sin[0] + off_z * g_cos[0] * g_cos[1];

    if (sync_rotation)
    {
        // Calculate the new rotation
        EDIT_FloatConvertValue(asin(g_cos[0] * g_cos[1]), atan2(g_sin[0], g_cos[0] * g_sin[1]) + offrz, atan2(g_cos[1] * g_cos[2] * g_sin[0] - g_sin[1] * g_sin[2], g_cos[2] * g_sin[1] - g_cos[1] * g_sin[0] * -g_sin[2]), g_sin, g_cos);
 	  	EDIT_FloatConvertValue(asin(g_cos[0] * g_sin[1]), atan2(g_cos[0] * g_cos[1], g_sin[0]), atan2(g_cos[2] * g_sin[0] * g_sin[1] - g_cos[1] * g_sin[2], g_cos[1] * g_cos[2] + g_sin[0] * g_sin[1] * g_sin[2]), g_sin, g_cos);
        EDIT_FloatConvertValue(atan2(g_sin[0], g_cos[0] * g_cos[1]) + offrx, asin(g_cos[0] * g_sin[1]), atan2(g_cos[2] * g_sin[0] * g_sin[1] + g_cos[1] * g_sin[2], g_cos[1] * g_cos[2] - g_sin[0] * g_sin[1] * g_sin[2]), g_sin, g_cos);

   	    RetRX = asin(g_cos[1] * g_sin[0]);
		RetRY = atan2(g_sin[1], g_cos[0] * g_cos[1]) + offry;
		RetRZ = atan2(g_cos[0] * g_sin[2] - g_cos[2] * g_sin[0] * g_sin[1], g_cos[0] * g_cos[2] + g_sin[0] * g_sin[1] * g_sin[2]);
    }
}





stock EDIT_FloatConvertValue(Float:rot_x, Float:rot_y, Float:rot_z, Float:sin[3], Float:cos[3])
{
    sin[0] = floatsin(rot_x, degrees);
    sin[1] = floatsin(rot_y, degrees);
    sin[2] = floatsin(rot_z, degrees);
    cos[0] = floatcos(rot_x, degrees);
    cos[1] = floatcos(rot_y, degrees);
    cos[2] = floatcos(rot_z, degrees);
    return 1;
}

/*
 * Fixes a bug that causes objects to not rotate
 * correctly when rotating on the Z axis only.
 */
stock EDIT_FloatEulerFix(&Float:rot_x, &Float:rot_y, &Float:rot_z)
{
    EDIT_FloatGetRemainder(rot_x, rot_y, rot_z);
    if((!floatcmp(rot_x, 0.0) || !floatcmp(rot_x, 360.0))
    && (!floatcmp(rot_y, 0.0) || !floatcmp(rot_y, 360.0)))
    {
        rot_y = 0.00000002;
    }
    return 1;
}

stock EDIT_FloatGetRemainder(&Float:rot_x, &Float:rot_y, &Float:rot_z)
{
    EDIT_FloatRemainder(rot_x, 360.0);
    EDIT_FloatRemainder(rot_y, 360.0);
    EDIT_FloatRemainder(rot_z, 360.0);
    return 1;
}

stock EDIT_FloatRemainder(&Float:remainder, Float:value)
{
    if(remainder >= value)
    {
        while(remainder >= value)
        {
            remainder = remainder - value;
        }
    }
    else if(remainder < 0.0)
    {
        while(remainder < 0.0)
        {
            remainder = remainder + value;
        }
    }
    return 1;
}